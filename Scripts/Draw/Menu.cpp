#include "Menu.h"
#include "Defaults.h"

std::vector<Menu*> Menus;

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
    Window->draw(Text, Transform);
}

Menu::Menu()
{
    MenuItems.push_back(new TextMenuItem("Test"));
    Menus.push_back(this);
}

void Menu::OnDisplay(sf::RenderWindow *Window)
{
    int i = 0;

    int Last;
    if (i = 0) Last = MenuItems.size();
    else Last = i-1;

    sf::Transform Transform;
    while (i < MenuItems.size())
    {
        MenuItems[i]->OnDisplay(Window, Transform);
        i++;
    }
}

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
{}
