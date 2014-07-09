#ifndef BASE
#define BASE

#include <SFML/Graphics.hpp>

namespace KNOW {
    void BaseDrawFunc();
    bool CursorCollisionCheck(sf::FloatRect CollisionShape);
    bool CursorCollisionCheck(sf::FloatRect CollisionShape, float Zoom);
}


#endif
