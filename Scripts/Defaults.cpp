#include <SFML/Graphics.hpp>

#include "Defaults.h"

namespace KNOW {
    sf::RenderWindow DefaultWindow(sf::VideoMode(1600, 900), "My window");
    sf::Font* DefaultFont = new sf::Font;
    PointOfView* BlockPOV;
    PointOfView MenuPOV;
}