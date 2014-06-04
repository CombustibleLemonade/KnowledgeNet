#include "Menu.h"
#include "Defaults.h"
#include <iostream>

std::vector<Menu*> Menus;

void MenuPOV::OnDisplay()
{
    MenuOfThisPOV->OnDisplay(&KNOW::DefaultWindow);
}

Menu MainMenu;

MenuItem::MenuItem()
{}

void MenuItem::OnDisplay(sf::RenderWindow * Window, sf::Transform Transform)
{}

TextMenuItem::TextMenuItem(const char *TextArg)
{
    FontToUse = KNOW::DefaultFont;
    Text.setString(TextArg);
    Text.setFont(*FontToUse);
    Text.setOrigin(Text.getGlobalBounds().width/2,
                   Text.getGlobalBounds().height);
}

void TextMenuItem::OnDisplay(sf::RenderWindow *Window, sf::Transform Transform)
{
    Window->draw(Text);
}

Menu::Menu()
{
    MenuItems.push_back(new TextMenuItem("Test"));
    Menus.push_back(this);
    POV.MenuOfThisPOV = this;
}

void Menu::OnDisplay(sf::RenderWindow *Window)
{
    int i = 0;

    int Last;
    if (i == 0) Last = MenuItems.size();
    else Last = i-1;

    sf::Transform Transform;
    while (i<MenuItems.size())
    {
        MenuItems[i]->OnDisplay(Window, Transform);
        i++;
    }
}

bool Menu::CollisionCheck(sf::RenderWindow *Window)
{}

void MenuDrawFunc(sf::RenderWindow* Window)
{
    int i = 0;
    while (i<Menus.size())
    {
        Menus[i]->OnDisplay(Window);
        i++;
    }
}

void MenuCollisionCheck(sf::RenderWindow *Window)
{
    int i = 0;
    while (i<Menus.size())
    {
        Menus[i]->CollisionCheck(Window);
        i++;
    }
}
