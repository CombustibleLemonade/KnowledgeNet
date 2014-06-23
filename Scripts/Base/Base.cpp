#include <iostream>
#include <vector>

#include "Base.h"
#include "Defaults.h"

namespace KNOW
{
    sf::Vector2f AbsoluteMousePosition(sf::RenderWindow& RelativeWindow)
    {
        sf::Vector2f Position =
                sf::Vector2f(sf::Mouse::getPosition(RelativeWindow));
        sf::View WindowView = RelativeWindow.getView();
        sf::Vector2f Windowsize = sf::Vector2f(RelativeWindow.getSize());
        sf::Vector2f MousePos;
        MousePos.x = (Position.x/Windowsize.x)*WindowView.getSize().x;
        MousePos.y = (Position.y/Windowsize.y)*WindowView.getSize().y;
        MousePos += WindowView.getCenter()-Windowsize/2.0f;
        //std::cout << MousePos.x << " " << MousePos.y << std::endl;

        return MousePos;
    }

    void BaseDrawFunc()
    {}

    bool CursorCollisionCheck(sf::FloatRect CollisionShape)
    {
        sf::Vector2f Position = AbsoluteMousePosition(KNOW::DefaultWindow);
        return CollisionShape.contains(Position);
    }
}
