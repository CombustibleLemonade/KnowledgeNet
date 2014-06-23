#include "Menu.h"
#include "Base/Defaults.h"
#include "Base/Base.h"

#include <iostream>
#include <ostream>
#include <sstream>

#include <string>
std::vector<KNOW::Menu*> Menus;

namespace KNOW{
    MenuItem::MenuItem()
    {}

    /* OnDisplay gets called everytime a frame is drawn. */
    void MenuItem::OnDisplay(int i)
    {}

    void MenuItem::OnCollision()
    {}

    void MenuItem::OnCollisionEntry()
    {}

    void MenuItem::OnCollisionExit()
    {}

    MenuItemLink::MenuItemLink()
    {
        Transformable.setFont(KNOW::DefaultFont);
    }

    MenuItemLink::MenuItemLink(const char *Text)
    {
        Transformable.setFont(KNOW::DefaultFont);
        Transformable.setString(Text);
    }

    void MenuItemLink::OnDisplay(int i)
    {
        bool PrevCollide = Collide;
        Collide = KNOW::CursorCollisionCheck(Transformable.getGlobalBounds());
        Transformable.setOrigin(floor(Transformable.getGlobalBounds().width/2),
                                floor(Transformable.getGlobalBounds().height/2));
        Transformable.setPosition(0, i*40);

        if (Collide)
        {
            OnCollision();
            if (!PrevCollide)
            {
                OnCollisionEntry();
            }
        }
        else if (PrevCollide)
        {
            OnCollisionExit();
        }
        PreviousLMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        KNOW::DefaultWindow.draw(Transformable);
    }

    void MenuItemLink::OnCollision()
    {
        bool LMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (LMBPressed && !PreviousLMBPressed)
        {
            std::cout << this << std::endl;
        }
    }

    void MenuItemLink::OnCollisionEntry()
    {
        Transformable.setColor(sf::Color(255, 0, 0));
    }

    void MenuItemLink::OnCollisionExit()
    {
        Transformable.setColor(sf::Color(255, 255, 255));
    }

    MenuRow::MenuRow()
    {
        MenuRowView.setCenter(0,0);
        MenuRowView.AdjustToScreenRes();

        for (int i = 0; i < 10; i++){
            MenuItems.push_back(new KNOW::MenuItemLink("Test"));
        }
    }

    void MenuRow::OnDisplay()
    {
        int ViewTop = fmin(MenuItems.size()*20,
                           MenuRowView.getSize().y/2-50);
        if(MenuRowView.getCenter().x<ViewTop)
        {
            MenuRowView.setCenter(0, ViewTop);
        }
        KNOW::DefaultWindow.setView(MenuRowView);
        for(int i = 0; i < MenuItems.size(); i++)
        {
            MenuItems[i]->OnDisplay(i);
        }
    }

    void Menu::PrivateOnDisplay()
    {
        for (int i = 0; i < MenuRows.size(); i++)
        {
            MenuRows[i]->OnDisplay();
        }
    }

    Menu::Menu()
    {
        Menus.push_back(this);
        MenuRows.push_back(new KNOW::MenuRow());
    }

    void Menu::OnDisplay()
    {
        for (int i = 0; i < Menus.size(); i++)
        {
            Menus[i]->PrivateOnDisplay();
        }
    }
}
