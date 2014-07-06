#include "Menu.h"
#include "Base/Defaults.h"
#include "Base/Base.h"

#include <cmath>
#include <iostream>
#include <string>


float Winning = 0;
bool DefaultTickBoxTarget = false;

namespace KNOW{
    sf::Texture MenuItemSlider::SlideTexture;
    int HorizontalMenuIndex = 0;

    std::vector<KNOW::Menu*> Menus;
    MenuRow* ActiveMenuRow;
    Menu* ActiveMenu;

    /* Virtual initializer*/
    MenuItem::MenuItem()
    {}

    void MenuItem::OnCollisionCheck()
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
        DisplayNext = false;
        Transformable = &Text;
        Text.setFont(KNOW::DefaultFont);
        Text.setString(TextArg);
    }

    /* This function is called upon a redisplay of the screen */
    void MenuItemLink::OnDisplay()
    {
        KNOW::DefaultWindow.draw(Text);
        if (DisplayNext)
        {
            if (ActiveMenu->HorizontalMenuSize == HorizontalMenuIndex)
            {
                DisplayNext = false;
                ActiveMenu->Focus = ActiveMenuRow;
                ActiveMenuRow->IsActiveMenu = true;
            }
            Next->OnDisplay();
            HorizontalMenuIndex += 1;
        }
    }

    void MenuItemLink::OnCollisionCheck()
    {
        if (DisplayNext && Next)
        {
            Next->OnDisplay();
        }
        else
        {
            bool PrevCollide = Collide;
            Collide = KNOW::CursorCollisionCheck(Text.getGlobalBounds());
            sf::Vector2f Origin = sf::Vector2f(floor(Text.getGlobalBounds().width/2),
                                               floor(Text.getGlobalBounds().height/2));
            Text.setOrigin(Origin);

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
        }
    }

    /* These functions are called when the cursor moves over the MenuItemLink. */
    void MenuItemLink::OnCollision()
    {
        //Next = new MenuRow;
        if (Next != NULL)
        {
            MenuRow* PreviousActive = ActiveMenuRow;
            Next->xLocation = ActiveMenuRow->xLocation + 750;
            Next->OnDisplay();

            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !PreviousLMBPressed && !DisplayNext)
            {
                DisplayNext = true;
                PreviousActive->IsActiveMenu = false;
                ActiveMenu->Focus = Next;
                ActiveMenu->HorizontalMenuSize++;
            }
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
        Value = &Winning;
        //*Value = 50;

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
        if (Value!=NULL)
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
        Text = "This is a MenuItemSlider: ";
        Collide = false;
        Value = NULL;
    }

    /* This function is called before each new frame is displayed. */
    void MenuItemSlider::OnDisplay()
    {
        Slider.Text = Text;
        if (Value!=NULL)
        {
            Slider.Value = Value;
        }
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

    sf::Texture MenuItemTickBox::TickBoxCubeTex;
    sf::Texture MenuItemTickBox::TickBoxVTex;

    void MenuItemTickBox::TickBox::OnCollision()
    {
        bool PrevLMBPressed = LMBPressed;
        LMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (LMBPressed && !PrevLMBPressed)
        {
            *Target = !*Target;
        }
    }

    void MenuItemTickBox::TickBox::OnCollisionEntry()
    {
        TickBoxCube.setColor(sf::Color(255, 0, 0));
    }

    void MenuItemTickBox::TickBox::OnCollisionExit()
    {
        TickBoxCube.setColor(sf::Color(255, 255, 255));
    }

    /* TickBox constructor. */
    MenuItemTickBox::TickBox::TickBox()
    {
        PrevText = "Test";
        Collide = false;
        TickBoxCubeTex.loadFromFile("Menu/CheckBoxBackground.png");
        TickBoxCube.setTexture(TickBoxCubeTex);
        TickBoxVTex.loadFromFile("Menu/CheckBoxV.png");
        TickBoxV.setTexture(TickBoxVTex);
        Name.setFont(KNOW::DefaultFont);
        Name.setString(": ");
    }

    /* TickBox drawing func. */
    void MenuItemTickBox::TickBox::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        if (Text != PrevText)
        {
            Name.setString(Text);
        }
        TickBoxV.setPosition(getPosition() + sf::Vector2f(4,0));
        TickBoxCube.setPosition(getPosition()+sf::Vector2f(0,-4));
        Name.setPosition(getPosition());
        sf::Vector2f Origin = sf::Vector2f(floor(Name.getGlobalBounds().width),
                                           floor(Name.getGlobalBounds().height/2));
        Name.setOrigin(Origin);
        if (*Target)
            target.draw(TickBoxV);
        target.draw(TickBoxCube);
        target.draw(Name);
        PrevText = Text;
    }

    void MenuItemTickBox::TickBox::CollisionCheck()
    {
        bool PrevCollide = Collide;
        Collide = KNOW::CursorCollisionCheck(TickBoxCube.getGlobalBounds());
        if(Collide)
        {
            if (!PrevCollide)
            {
                OnCollisionEntry();
            }
            OnCollision();
        }
        else if(PrevCollide)
        {
            OnCollisionExit();
        }
    }

    /* Constructor for MenuItemTickBox. */
    MenuItemTickBox::MenuItemTickBox()
    {
        Target = &DefaultTickBoxTarget;
        Transformable = &Box;
    }

    /* This function is called before each new frame is displayed. */
    void MenuItemTickBox::OnDisplay()
    {
        Box.Target = Target;
        Box.Text = Text;
        KNOW::DefaultWindow.draw(Box);
    }

    void MenuItemTickBox::OnCollisionCheck()
    {
        Box.CollisionCheck();
    }

    void MenuItemButton::OnCollision()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            KNOW::DefaultWindow.close();
    }

    void MenuItemButton::OnCollisionEntry()
    {
        Text.setColor(sf::Color(255, 0, 0));
    }

    void MenuItemButton::OnCollisionExit()
    {
        Text.setColor(sf::Color(255, 255, 255));
    }

    /* Constructor for MenuItemButton. */
    MenuItemButton::MenuItemButton()
    {
        Transformable = &Text;
        Text.setFont(KNOW::DefaultFont);
        Collide = false;
    }

    /* This function is called before each new frame is displayed. */
    void MenuItemButton::OnDisplay()
    {
        KNOW::DefaultWindow.draw(Text);
    }

    void MenuItemButton::OnCollisionCheck()
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            OnClicked();
        sf::Vector2f Origin = sf::Vector2f(floor(Text.getGlobalBounds().width/2),
                                           floor(Text.getGlobalBounds().height/2));
        Text.setOrigin(Origin);
        bool PrevCollide = Collide;
        Collide = KNOW::CursorCollisionCheck(Text.getGlobalBounds());
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
    }

    /* Constructor for MenuRow. */
    MenuRow::MenuRow()
    {
        Scroll = 0;
        HorizontalSize = 0;
        MenuRowView.setCenter(0,0);
        MenuRowView.AdjustToScreenRes();
        xLocation = 0;
        IsActiveMenu = true;
    }

    /* This function is called before each new frame is displayed. */
    void MenuRow::OnDisplay()
    {
        ActiveMenuRow = this;
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
            if (IsActiveMenu == true)
            {
                MenuItems[i]->OnCollisionCheck();
            }
            MenuItems[i]->OnDisplay();
        }
    }

    /* Constructor for Menu. */
    Menu::Menu()
    {
        MenuView.setCenter(0,0);
        MenuView.AdjustToScreenRes();
        Focus = &BaseRow;
        TargetPosition = sf::Vector2f(0,0);
        HorizontalMenuSize = 0;
    }

    /* This function is called before each new frame is displayed. */
    void Menu::OnDisplay()
    {
        ActiveMenu = this;
        HorizontalMenuIndex = 0;
        if (MenuView.getCenter().x < Focus->xLocation)
        {
            float Delta = (Focus->xLocation-MenuView.getCenter().x)*0.00001 + 0.00001;
            Delta *= KNOW::DeltaTime.asMicroseconds();
            if (MenuView.getCenter().x + Delta < Focus->xLocation)
            {
                MenuView.move(Delta, 0);
            }
            else
            {
                MenuView.setCenter(Focus->xLocation, 0);
            }
        }
        if (MenuView.getCenter().x > Focus->xLocation)
        {
            float Delta = (Focus->xLocation-MenuView.getCenter().x)*0.00001 - 0.00001;
            Delta *= KNOW::DeltaTime.asMicroseconds();
            MenuView.move(Delta, 0);
        }
        KNOW::DefaultWindow.setView(MenuView);
        BaseRow.OnDisplay();
    }

    /* This function will return the user to the previous MenuRow. */
    bool Menu::PopBack()
    {
        if (HorizontalMenuSize>0)
            HorizontalMenuSize--;
        else
            return false;
        return true;
    }
}
