#ifndef POV_SWITCHING
#define POV_SWITCHING

#include <SFML/Graphics.hpp>

namespace KNOW
{
    /* KNOW::View is a class which inherits from the sf::view class.*/
    class View: public sf::View
    {
    public:
        View();
        static void OnDisplay();
        sf::Vector2f Location;
        float ZoomValue;
        void AdjustToScreenRes();
    };
}

#endif
