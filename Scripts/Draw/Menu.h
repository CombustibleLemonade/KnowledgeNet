#ifndef MENU_DRAWING
#define MENU_DRAWING

#include <string>
#include <SFML/Graphics.hpp>

#include "PointOfView.h"

class Menu;

class MenuPOV : public PointOfView
{
public:
    Menu* MenuOfThisPOV;
    void OnDisplay();
};

class MenuItem
{
public:
    MenuItem();

    virtual void OnDisplay(sf::RenderWindow * Window, sf::Transform Transform);
};

class TextMenuItem: public MenuItem
{
public:
    TextMenuItem(const char* TextArg);


    sf::Font * FontToUse;
    sf::Text Text;

    void OnDisplay(sf::RenderWindow * Window, sf::Transform Transform);
};

class Menu
{
public:
    std::vector<MenuItem*> MenuItems;
    Menu();
    MenuPOV POV;
    bool Display;
    void OnDisplay(sf::RenderWindow * Window);
    bool CollisionCheck(sf::RenderWindow* Window);
};

void MenuDrawFunc(sf::RenderWindow * Window);

void MenuCollisionCheck(sf::RenderWindow * Window);

#endif
