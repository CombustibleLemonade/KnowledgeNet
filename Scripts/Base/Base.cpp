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
        sf::Vector2f WindowSize = sf::Vector2f(RelativeWindow.getSize());
        sf::Vector2f ViewSize = sf::Vector2f(WindowView.getSize());
        sf::Vector2f MousePos;
        float Zoom = ViewSize.x/WindowSize.x;

        MousePos.x = (Position.x/ViewSize.x)*WindowView.getSize().x;
        MousePos.y = (Position.y/ViewSize.y)*WindowView.getSize().y;
        MousePos += WindowView.getCenter()/Zoom-WindowSize/2.0f;
        MousePos *= Zoom;


        return MousePos;
    }

    void BaseDrawFunc()
    {}

    bool CursorCollisionCheck(sf::FloatRect CollisionShape)
    {
        sf::Vector2f Position = AbsoluteMousePosition(KNOW::DefaultWindow);
        return CollisionShape.contains(Position);
    }

    bool CursorCollisionCheck(sf::FloatRect CollisionShape, float Zoom)
    {
        sf::Vector2f Position = AbsoluteMousePosition(KNOW::DefaultWindow);
        return CollisionShape.contains(Position);
    }

    void CenterOrigin(sf::Sprite &SpriteToCenter)
    {
        sf::FloatRect SpriteRect = SpriteToCenter.getLocalBounds();
        SpriteToCenter.setOrigin(SpriteRect.width/2, SpriteRect.height/2);
    }
}
