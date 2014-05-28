#ifndef POV_SWITCHING
#define POV_SWITCHING

#include <SFML/Graphics.hpp>

class PointOfView
{
public:
    sf::RenderWindow * WindowToRenderTo;
    PointOfView();
    void OnDisplay();

    void  (*DisplayFunc) (sf::RenderWindow* Window);
    sf::View View;
};

void POVDrawFunc();

void ManageViews();

#endif
