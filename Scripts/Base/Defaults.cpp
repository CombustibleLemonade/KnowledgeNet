#include <iostream>
#include <SFML/Graphics.hpp>

#include "Defaults.h"
#include "Draw/Menu.h"

namespace KNOW
{
    sf::RenderWindow DefaultWindow(sf::VideoMode(1600, 900), "My window");
    sf::Font DefaultFont;
    bool DisplayMenu = true;
    MenuRow MainMenu;
    sf::Time DeltaTime;
    float ClickVolume = 50;
}
