#ifndef MENU_DRAWING
#define MENU_DRAWING

#include <string>
#include <SFML/Graphics.hpp>

class MenuItem
{
public:
    MenuItem();
    MenuItem(const char* Text);
    std::string Text;
};

class Menu
{
public:
    bool Display;
    void OnDisplay(sf::RenderWindow * Window);
};

void MenuDrawFunc();

#endif
