#ifndef BASE
#define BASE

#include <SFML/Graphics.hpp>
#include <functional>

namespace KNOW {
    class KeyBinding{
        sf::Keyboard::Key KeyboardKey;
        sf::Mouse::Button MouseButton;
        sf::Joystick::Axis JoystickAxis;
    public:
        bool Bind(sf::Keyboard::Key KeyboardKeyArg);
        bool Bind(sf::Mouse::Button MouseButtonArg);
        bool Bind(sf::Joystick::Axis JoystickAxisArg);

        void QueueForRebind();
        void UnqueueForRebind();
    };

    class Profiler
    {
        sf::Clock Measure;
    public:
        Profiler();
        sf::Time operator ()();
    };

    class Call
    {
        static std::vector<float> AllCalls;
    public:
        std::function<void(void)> Function;
        void operator()();
    };

    void BaseDrawFunc();
    bool CursorCollisionCheck(sf::FloatRect CollisionShape);
    bool CursorCollisionCheck(sf::FloatRect CollisionShape, float Zoom);

    void CenterOrigin(sf::Sprite &SpriteToCenter);
}

#endif
