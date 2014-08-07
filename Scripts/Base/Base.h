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

    class Animation
    {
    public:
        virtual float Y(sf::Time X);
    };

    class AnimationBezierCurve: public Animation
    {};

    class AnimationLinear: public Animation
    {
        class LineCurvePoint
        {
            sf::Time X;
            float Y;
        };
        std::vector<LineCurvePoint> Points;
    public:
        float Y (sf::Time X);
    };

    class AnimationFunction
    {
    public:
        float Y(sf::Time X);
    };

    void BaseDrawFunc();
    bool CursorCollisionCheck(sf::FloatRect CollisionShape);
    bool CursorCollisionCheck(sf::FloatRect CollisionShape, float Zoom);

    void CenterOrigin(sf::Sprite &SpriteToCenter);
}

#endif
