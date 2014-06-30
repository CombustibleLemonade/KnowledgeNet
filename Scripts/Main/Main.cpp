#include <iostream>

#include <SFML/Graphics.hpp>

#include "Base/Base.h"
#include "Base/Defaults.h"
#include "Draw/Block.h"
#include "Draw/PointOfView.h"
#include "Draw/Menu.h"

sf::Vector2i LastMouseLocation;

int main ()
{
    KNOW::DefaultFont.loadFromFile("PixelatedFont/SFPixelate-Bold.ttf");

    KNOW::Menu TestMenu;

    KNOW::View Viewer;

    while (KNOW::DefaultWindow.isOpen())
    {
        sf::Event Event;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !KNOW::DisplayMenu)
        {}
        LastMouseLocation = sf::Mouse::getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {}

        while (KNOW::DefaultWindow.pollEvent(Event))
        {
            if (Event.type == sf::Event::MouseWheelMoved && !KNOW::DisplayMenu)
            {
                if (Event.mouseWheel.delta == 1)
                {}
                else
                {}
            }
            if (Event.type == sf::Event::KeyPressed)
            {
                if (Event.key.code == sf::Keyboard::Escape)
                {KNOW::DefaultWindow.close();}
                if (Event.key.code == sf::Keyboard::F1){
                    KNOW::DisplayMenu = !KNOW::DisplayMenu;
                }
            }
            if (Event.type == sf::Event::Closed)
            {
                KNOW::DefaultWindow.close();
            }
            if (Event.type == sf::Event::Resized)
            {}
        }
        KNOW::DefaultWindow.clear(sf::Color(128, 128, 128));

        KNOW::View::OnDisplay();

        if (!KNOW::DisplayMenu)
        {}
        else if (KNOW::DisplayMenu)
        {
            TestMenu.OnDisplay();
        }
        KNOW::DefaultWindow.display();
    }
    return 0;
}
