#include <iostream>

#include <SFML/Graphics.hpp>

#include "Base/Base.h"
#include "Base/Defaults.h"
#include "Draw/Block.h"
#include "Draw/PointOfView.h"
#include "Draw/Menu.h"

sf::Vector2i LastMouseLocation;
sf::Clock DeltaTimeClock;

int main ()
{
    KNOW::Block::BlockView.setCenter(0,0);
    KNOW::DefaultFont.loadFromFile("PixelatedFont/SFPixelate-Bold.ttf");
    KNOW::DefaultWindow.create(sf::VideoMode(1920, 1080), "Winning", sf::Style::Fullscreen);

    KNOW::Menu TestMenu;
    KNOW::MenuItemLink* MILHandle;
    KNOW::MenuItemSlider* MISHandle;
    KNOW::MenuItemTickBox* MITHandle;
    KNOW::MenuItemButton* MIBHandle;

    KNOW::MenuRow* MenuRowHandle;

    MenuRowHandle = new KNOW::MenuRow;

    MISHandle = new KNOW::MenuItemSlider;
    MISHandle->Text = "Click Volume: ";
    MISHandle->Value = &KNOW::ClickVolume;
    MenuRowHandle = new KNOW::MenuRow;
    MenuRowHandle->MenuItems.push_back(MISHandle);
    MITHandle = new KNOW::MenuItemTickBox;
    MILHandle = new KNOW::MenuItemLink("Audio");
    MILHandle->Next = MenuRowHandle;
    TestMenu.BaseRow.MenuItems.push_back(MILHandle);

    MISHandle = new KNOW::MenuItemSlider;
    MISHandle->Text = "Brightness: ";
    MenuRowHandle = new KNOW::MenuRow;
    MenuRowHandle->MenuItems.push_back(MISHandle);
    MITHandle = new KNOW::MenuItemTickBox;
    MITHandle->Text = "Fullscreen: ";
    MITHandle->OnTrue = []()
    {
        KNOW::DefaultWindow.create(sf::VideoMode(1920, 1080), "KNOW", sf::Style::Fullscreen);
    };
    MITHandle->OnFalse = []()
    {
        KNOW::DefaultWindow.create(sf::VideoMode(1280, 720), "KNOW");
    };
    MITHandle->Target = &KNOW::IsFullscreen;
    MenuRowHandle->MenuItems.push_back(MITHandle);
    MILHandle = new KNOW::MenuItemLink("Graphics");
    MILHandle->Next = MenuRowHandle;
    TestMenu.BaseRow.MenuItems.push_back(MILHandle);

    MIBHandle = new KNOW::MenuItemButton;
    MIBHandle->OnClicked = [](){};
    MIBHandle->Text.setString("Quit");
    TestMenu.BaseRow.MenuItems.push_back(MIBHandle);

    KNOW::View Viewer;

    //KNOW::DefaultWindow.create(sf::VideoMode(1920, 1080), "Testing", sf::Style::Fullscreen);
    while (KNOW::DefaultWindow.isOpen())
    {
        KNOW::DeltaTime = DeltaTimeClock.getElapsedTime();
        DeltaTimeClock.restart();
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
                KNOW::Block::Zoom(Event.mouseWheel.delta);
            }
            if (Event.type == sf::Event::KeyPressed)
            {
                if (Event.key.code == sf::Keyboard::Escape)
                {
                    if (!TestMenu.PopBack())
                    {
                        KNOW::DisplayMenu = !KNOW::DisplayMenu;
                    }
                }
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
        {
            KNOW::Block::CollisionCheck();
        }

        KNOW::Block::Draw();

        if (KNOW::DisplayMenu)
        {
            TestMenu.OnDisplay();
        }
        KNOW::DefaultWindow.display();
    }
    return 0;
}
