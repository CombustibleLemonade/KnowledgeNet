#include <iostream>

#include <SFML/Graphics.hpp>

#include "Base/Base.h"
#include "Defaults.h"
#include "Draw/Block.h"
#include "Draw/PointOfView.h"
#include "Draw/Menu.h"


using namespace std;

bool BlockViewDrag = false;

sf::Vector2f MouseLocation;

sf::Vector2f ViewingLocation;
sf::Vector2f dViewingLocation;
sf::Vector2i LastMouseLocation;
float Zoom = 2;

void UpdateView(PointOfView* ViewToUpdate)
{
    ViewToUpdate->View.setCenter(ViewingLocation.x,ViewingLocation.y);
    ViewToUpdate->View.setSize(ViewToUpdate->WindowToRenderTo->getSize().x,
                               ViewToUpdate->WindowToRenderTo->getSize().y);
    ViewToUpdate->View.zoom(Zoom);
}

int main ()
{
    KNOW::DefaultFont->loadFromFile("PixelatedFont/SFPixelate-Bold.ttf");

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

    Menu TestMenu;
    PointOfView MenuPOV;
    MenuPOV.DisplayFunc = MenuDrawFunc;

    PointOfView BlockView;
    BlockView.DisplayFunc = BlockDrawFunc;

    UpdateView(&BlockView);

    while (KNOW::DefaultWindow.isOpen())
    {
        sf::Event Event;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
            //KNOW::TrackMovement (ViewingLocation, &BlockViewDrag, sf::Mouse::getPosition())
            dViewingLocation = sf::Vector2f(sf::Mouse::getPosition() - LastMouseLocation);
            ViewingLocation -= dViewingLocation*Zoom;
            UpdateView(&BlockView);
        }
        LastMouseLocation = sf::Mouse::getPosition();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            KNOW::DefaultWindow.close();
        }
        while (KNOW::DefaultWindow.pollEvent(Event))
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
                KNOW::DefaultWindow.close();
            }
            if (Event.type == sf::Event::Resized)
            {
                UpdateView(&BlockView);
            }
        }
        KNOW::BaseDrawFunc();
        KNOW::DefaultWindow.clear(sf::Color(128, 128, 128));
        POVDrawFunc();
        CollisionCheck(&KNOW::DefaultWindow,
                       sf::Vector2f(sf::Mouse::getPosition(KNOW::DefaultWindow)),
                       Zoom);

        KNOW::DefaultWindow.display();
    }
    return 0;
}
