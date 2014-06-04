#include <vector>

#include "Base.h"
#include "Defaults.h"

namespace KNOW {
    void BaseDrawFunc()
    {}

    bool CursorCollisionCheck(sf::FloatRect CollisionShape)
    {
        return CollisionShape.contains(sf::Vector2f(sf::Mouse::getPosition(KNOW::DefaultWindow)));
    }
}
