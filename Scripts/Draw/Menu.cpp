#include "Menu.h"
#include "Defaults.h"

std::vector<Menu*> Menus;

MenuItem::MenuItem()
{}

MenuItem::MenuItem(const char *TextArg)
{
    FontToUse = KNOW::DefaultFont;
    Text.setString(TextArg);
    Text.setFont(*FontToUse);
    Text.setOrigin(Text.getGlobalBounds().width/2, 0);
}

void MenuItem::OnDisplay(sf::RenderWindow * Window)
{
    Window->draw(Text);
}

Menu::Menu()
{
    MenuItems.push_back(MenuItem("Test"));
    Menus.push_back(this);
}

void Menu::OnDisplay(sf::RenderWindow *Window)
{
    int i = 0;
    while (i < MenuItems.size())
    {
        MenuItems[i].OnDisplay(Window);
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
