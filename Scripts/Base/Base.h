#ifndef BASE
#define BASE

#include <SFML/Graphics.hpp>

namespace KNOW {
    class KeyBinding{
        sf::Keyboard::Key KeyboardKey;
        sf::Mouse::Button MouseButton;
        sf::Joystick::Axis JoystickAxis;
    public:
        bool Bind(sf::Keyboard::Key KeyboardKeyArg);
        bool Bind(sf::Mouse::Button MouseButtonArg);
        bool Bind(sf::Joystick::Axis JoystickAxisArg);
    };


    void BaseDrawFunc();
    bool CursorCollisionCheck(sf::FloatRect CollisionShape);
    bool CursorCollisionCheck(sf::FloatRect CollisionShape, float Zoom);
}

#endif
