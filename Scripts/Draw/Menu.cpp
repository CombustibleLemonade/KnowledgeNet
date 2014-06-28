#include "Menu.h"
#include "Base/Defaults.h"
#include "Base/Base.h"

#include <iostream>
#include <string>
std::vector<KNOW::Menu*> Menus;


namespace KNOW{
    sf::Texture MenuItemSlider::SlideTexture;

    /* Virtual initializer*/
    MenuItem::MenuItem()
    {}

    /* This function is called upon a redisplay of the screen */
    void MenuItem::OnDisplay()
    {}

    /* Initialize Transformable */
    MenuItemLink::MenuItemLink()
    {
        Transformable = &Text;
        Text.setFont(KNOW::DefaultFont);
    }

    MenuItemLink::MenuItemLink(const char *TextArg)
    {
        Next = NULL;
        Transformable = &Text;
        Text.setFont(KNOW::DefaultFont);
        Text.setString(TextArg);
    }

    /* This function is called upon a redisplay of the screen */
    void MenuItemLink::OnDisplay()
    {
        bool PrevCollide = Collide;
        Collide = KNOW::CursorCollisionCheck(Text.getGlobalBounds());
        Text.setOrigin(floor(Text.getGlobalBounds().width/2),
                                ceil(Text.getGlobalBounds().top/2+0.1));

        if (Collide)
        {
            if (!PrevCollide)
            {
                OnCollisionEntry();
            }
            OnCollision();
        }
        else if (PrevCollide)
        {
            OnCollisionExit();
        }
        PreviousLMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        KNOW::DefaultWindow.draw(Text);
    }

    /* These functions are called when the cursor moves over the MenuItemLink. */
    void MenuItemLink::OnCollision()
    {
        if (Next != NULL)
        {
            Next->xLocation = 300;
            Next->OnDisplay();
        }
    }

    void MenuItemLink::OnCollisionEntry()
    {
        Text.setColor(sf::Color(255, 0, 0));
    }

    void MenuItemLink::OnCollisionExit()
    {
        Text.setColor(sf::Color(255, 255, 255));
    }

    /* Function which is called by all initializers. */
    void MenuItemSlider::SliderBar::InitObjects()
    {
        Value = new float;
        *Value = 50;

        Min = 0;
        Max = 100;

        LMBPressed = false;

        BackgroundSprite.setTexture(MenuItemSlider::SlideTexture);
        BackgroundSprite.setTextureRect(sf::IntRect(0, 0, 300, 22));
        BackgroundSprite.setPosition(0,0);

        TextDrawable.setFont(KNOW::DefaultFont);
        ValueDisplay.setFont(KNOW::DefaultFont);
    }

    /* These functions are called when the cursor moves over the MenuItemSlider::SliderBar. */
    void MenuItemSlider::SliderBar::OnCollision()
    {
        PrevLMBPressed = LMBPressed;
        LMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (LMBPressed && !PrevLMBPressed)
        {
            OnDragEntry();
        }
    }

    void MenuItemSlider::SliderBar::OnCollisionEntry()
    {
        Rectangle.setFillColor(sf::Color(255, 0, 0));
    }

    void MenuItemSlider::SliderBar::OnCollisionExit()
    {
        Rectangle.setFillColor(sf::Color(255, 255, 255));
    }

    /* These functions are called while the SliderBar is beeing dragged by the mouse. */
    void MenuItemSlider::SliderBar::OnDrag()
    {
        float DeltaMousePos = sf::Mouse::getPosition().x - PrevMouseXPos;
        *Value = PrevSliderValue + DeltaMousePos*(Max-Min)/(300-Rectangle.getSize().x);
    }

    void MenuItemSlider::SliderBar::OnDragEntry()
    {
        PrevSliderValue = *Value;
        PrevMouseXPos = sf::Mouse::getPosition().x;
        IsSliding = true;
    }

    void MenuItemSlider::SliderBar::OnDragExit()
    {
        IsSliding = false;
        if (!CursorCollisionCheck(Rectangle.getGlobalBounds()))
            Rectangle.setFillColor(sf::Color(255, 255, 255));
    }

    /* Constructors for MenuItemSlider::SliderBar. */
    MenuItemSlider::SliderBar::SliderBar()
    {
        InitObjects();
        Text = "This is a slider: ";
    }

    MenuItemSlider::SliderBar::SliderBar(const char* TextArg)
    {
        InitObjects();
        TextDrawable.setString(TextArg);
        Text = TextArg;
    }

    /* This function fixes abstractness and gets called upon sf::RenderWindow::draw. */
    void MenuItemSlider::SliderBar::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if (Value)
        {
            if (*Value<Min)
                *Value = Min;
            else if (*Value > Max)
                *Value = Max;
        }
        ValueDisplay.setString(std::to_string(int(*Value)) + "%");
        sf::FloatRect TextRect = ValueDisplay.getGlobalBounds();
        float TextHeight = TextRect.height;
        ValueDisplay.setOrigin(0, floor(TextHeight/2));
        ValueDisplay.setPosition(getPosition() + sf::Vector2f(310, 0));
        //ValueDisplay.setColor(sf::Color(*Value*2.55, *Value*1.27, *Value*2.55));

        TextDrawable.setString(Text);
        TextRect = TextDrawable.getGlobalBounds();
        TextHeight = TextRect.height;
        TextDrawable.setOrigin(floor(TextRect.width),
                               floor(TextHeight/2));
        TextDrawable.setPosition(getPosition());

        BackgroundSprite.setPosition(getPosition());

        target.draw(TextDrawable, states);
        target.draw(BackgroundSprite, states);
        target.draw(ValueDisplay, states);

        if (Value)
        {
            Rectangle.setPosition(getPosition() +
                                  sf::Vector2f(CursorToSliderXPos(*Value), 0));
            Rectangle.setSize(sf::Vector2f(16, TextHeight));
            if(IsSliding)
                Rectangle.setFillColor(sf::Color(255, 0, 0));

            target.draw(Rectangle, states);
        }
    }

    /* Cursor & Slider conversion functions. */
    float MenuItemSlider::SliderBar::CursorToSliderXPos(float CursorX) const
    {
        float SliderRange = Max-Min;
        float RectPosition = ((CursorX-Min)/SliderRange);
        float SliderSize = 300-Rectangle.getSize().x;
        return RectPosition*SliderSize;
    }

    float MenuItemSlider::SliderBar::SliderToCursorXPos(float SliderX) const
    {
        float SliderRange = Max-Min;
        float SliderSize = 300-Rectangle.getSize().x;
        return ((SliderX/SliderSize)*SliderRange) + Min;
    }

    /* Functions for changing properties of MenuItemSlider::Sliderbar objects. */
    sf::FloatRect MenuItemSlider::SliderBar::getGlobalBounds()
    {
        return Rectangle.getGlobalBounds();
    }

    void MenuItemSlider::SliderBar::setRectangleColor(sf::Color ColorArg)
    {
        Rectangle.setFillColor(ColorArg);
    }

    /* Constructor for MenuItemSlider. */
    MenuItemSlider::MenuItemSlider()
    {
        MenuItemSlider::SlideTexture.loadFromFile("Menu/SliderBackground.png");

        Transformable = &Slider;
        Text = "Winning!";
        Collide = false;
    }

    /* This function is called before each new frame is displayed. */
    void MenuItemSlider::OnDisplay()
    {
        if (Slider.IsSliding && sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            Slider.OnDrag();
        }
        else if (Slider.IsSliding)
        {
            Slider.OnDragExit();
        }
        Collide = CursorCollisionCheck(Slider.getGlobalBounds());
        if(Collide)
        {
            if (!PrevCollide)
            {
                Slider.OnCollisionEntry();
            }
            Slider.OnCollision();
        }
        else if(PrevCollide)
        {
            Slider.OnCollisionExit();
        }
        PrevCollide = Collide;
        KNOW::DefaultWindow.draw(Slider);
    }

    /* Constructor for MenuRow. */
    MenuRow::MenuRow()
    {
        Scroll = 0;
        HorizontalSize = 0;
        MenuRowView.setCenter(0,0);
        MenuRowView.AdjustToScreenRes();
        xLocation = 0;

        MenuItems.push_back(new MenuItemSlider);
        MenuItems.push_back(new MenuItemLink("This is a link to a MenuRow"));
    }

    /* This function is called before each new frame is displayed. */
    void MenuRow::OnDisplay()
    {

        sf::View CurrentView = KNOW::DefaultWindow.getView();
        int VectorSize = MenuItems.size();
        int ScrollMax = fmax(-CurrentView.getSize().y/2,
                             -VectorSize*20);
        if (ScrollMax<Scroll)
            Scroll = ScrollMax;

        int ScrollMin = fmin(CurrentView.getSize().y/2-VectorSize*40,
                             -VectorSize*20);
        if (ScrollMin>Scroll)
            Scroll = ScrollMin;

        for(int i = 0; i < MenuItems.size(); i++)
        {
            MenuItems[i]->Transformable->setPosition(xLocation, i*40 + Scroll);
            MenuItems[i]->OnDisplay();
        }
    }

    void Menu::PrivateOnDisplay()
    {
        KNOW::DefaultWindow.setView(MenuView);
        int Distance = 0;
        for (int i = 0; i < MenuRows.size(); i++)
        {
            MenuRows[i]->xLocation = i*700;
            MenuRows[i]->OnDisplay();
            Distance += MenuRows[i]->HorizontalSize/2;
        }
    }

    /* Constructor for Menu. */
    Menu::Menu()
    {
        Menus.push_back(this);
        MenuRows.push_back(new KNOW::MenuRow());
        MenuRows.push_back(new KNOW::MenuRow());

        MenuView.setCenter(0,0);
        MenuView.AdjustToScreenRes();
    }

    /* This function is called before each new frame is displayed. */
    void Menu::OnDisplay()
    {
        for (int i = 0; i < Menus.size(); i++)
        {
            Menus[i]->PrivateOnDisplay();
        }
    }
}
