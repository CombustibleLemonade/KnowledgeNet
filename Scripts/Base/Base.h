#ifndef BASE
#define BASE

#include <SFML/Graphics.hpp>

namespace KNOW {
    class TrackMovement
    {
        sf::Vector2f* Target;
        sf::Vector2f DeltaTarget;
        sf::Vector2f PreviousSourceLocation;

        bool* MoveWhen;
        sf::Vector2f* Source;
            bool UseFuncPointer;
    public:
        TrackMovement(sf::Vector2f* TargetArg, bool *MoveWhenArg, sf::Vector2f* SourceArg);
        void OnDisplay();
    };

    void BaseDrawFunc();
}


#endif
