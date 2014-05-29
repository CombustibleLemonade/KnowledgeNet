#ifndef MENU_DRAWING
#define MENU_DRAWING

#include <string>
#include <SFML/Graphics.hpp>

class MenuItem
{
public:
    MenuItem();
    MenuItem(const char* TextArg);

    sf::Font * FontToUse;
    sf::Text Text;

    void SetText(const char* TextArg);
    void OnDisplay(sf::RenderWindow * Window);

};

class Menu
{
public:
    std::vector<MenuItem> MenuItems;
    Menu();
    bool Display;
    sf::Vector2f TopLeftPosition;
    void OnDisplay(sf::RenderWindow * Window);
};

void MenuDrawFunc(sf::RenderWindow * Window);

#endif
