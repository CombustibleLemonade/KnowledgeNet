#include <iostream>
#include <SFML/Graphics.hpp>

#include "Defaults.h"
#include "Draw/Menu.h"

namespace KNOW
{
    sf::RenderWindow DefaultWindow(sf::VideoMode(1600, 900), "My window");
    sf::Font DefaultFont;
    bool IsFullscreen = true;
    bool DisplayMenu = true;
    bool DisplayPage = false;
    MenuRow MainMenu;
    sf::Time ASDF;
    float ClickVolume = 50;
}
