#ifndef POV_SWITCHING
#define POV_SWITCHING

#include <SFML/Graphics.hpp>

class PointOfView
{
public:
    PointOfView();

    sf::Vector2f Location;

    bool DoesDisplay;
    sf::RenderWindow * WindowToRenderTo;
    sf::View View;

    void OnDisplay();
    void  (*DisplayFunc) (sf::RenderWindow* Window);
};

void POVDrawFunc();

void ManageViews();

#endif
