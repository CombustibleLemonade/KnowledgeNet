#include <iostream>
#include <SFML/Graphics.hpp>

#include "Defaults.h"
#include "Draw/Menu.h"

namespace KNOW
{
    sf::RenderWindow DefaultWindow(sf::VideoMode(1600, 900), "My window");
    sf::Font DefaultFont;
    bool IsFullscreen = false;
    bool DisplayMenu = true;
    bool DisplayPage = false;
    MenuRow MainMenu;
    sf::Time MenuDelta;
    float ClickVolume = 50;
}
