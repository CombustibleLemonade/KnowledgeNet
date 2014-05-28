#include <iostream>

#include <SFML/Graphics.hpp>

#include "Defaults.h"
#include "Draw/Block.h"
#include "Draw/PointOfView.h"
#include "Draw/Menu.h"


using namespace std;



sf::Vector2f ViewingLocation;
sf::Vector2f dViewingLocation;
sf::Vector2i LastMouseLocation;
float Zoom = 2;

void UpdateView(PointOfView* ViewToUpdate)
{
    sf::View View(sf::FloatRect(ViewingLocation.x,ViewingLocation.y,
                                ViewToUpdate->WindowToRenderTo->getSize().x,
                                ViewToUpdate->WindowToRenderTo->getSize().y));
    ViewToUpdate->View.setCenter(ViewingLocation.x,ViewingLocation.y);
    ViewToUpdate->View.setSize(ViewToUpdate->WindowToRenderTo->getSize().x,
                               ViewToUpdate->WindowToRenderTo->getSize().y);
    ViewToUpdate->View.zoom(Zoom);
}

int main ()
{
    sf::Texture Backdrop;
    if (!Backdrop.loadFromFile("Backdrop.png", sf::IntRect(0,0,512,512)))
        return -1;
    Backdrop.setSmooth(true);
    SetIconBackdrop(Backdrop);

    Block PlusBlock("IconPlus.png");
    PlusBlock.SetPosition(sf::Vector2f(0, 0));
    Block MinusBlock("IconMinus.png");
    MinusBlock.SetPosition(sf::Vector2f(1024, 256));

    PlusBlock.AddNextBlock(&MinusBlock);

    sf::RenderWindow Window(sf::VideoMode(1600, 900), "My window");
    KNOW::DefaultWindow = &Window;

    PointOfView BlockView;
    BlockView.DisplayFunc = BlockDrawFunc;

    UpdateView(&BlockView);

    while (Window.isOpen())
    {
        sf::Event Event;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
            dViewingLocation = sf::Vector2f(sf::Mouse::getPosition() - LastMouseLocation);
            ViewingLocation -= dViewingLocation*Zoom;
            UpdateView(&BlockView);
        }
        LastMouseLocation = sf::Mouse::getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            Window.close();
        }
        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::MouseWheelMoved)
            {
                if (Event.mouseWheel.delta == 1)
                {
                    Zoom /= 1.1;
                }
                else
                {
                    Zoom *= 1.1;
                }
                UpdateView(&BlockView);
            }
            if (Event.type == sf::Event::Closed)
            {
                Window.close();
            }
            if (Event.type == sf::Event::Resized)
            {
                UpdateView(&BlockView);
            }
        }
        CollisionCheck(&Window, sf::Vector2f(sf::Mouse::getPosition(Window)), Zoom);
        Window.clear(sf::Color(128, 128, 128));
        POVDrawFunc();
        Window.display();
    }

    return 0;
}
