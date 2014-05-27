#include <iostream>
#include "Block.h"

#include <SFML/Graphics.hpp>

using namespace std;

sf::Vector2f ViewingLocation;
sf::Vector2f dViewingLocation;
sf::Vector2i LastMouseLocation;
float Zoom = 2;

void UpdateView(sf::RenderWindow * Window)
{
    sf::View View(sf::FloatRect(ViewingLocation.x,ViewingLocation.y,
                                Window->getSize().x, Window->getSize().y));
    View.zoom(Zoom);
    Window->setView(View);
}

int main ()
{
    sf::Texture Backdrop;
    if (!Backdrop.loadFromFile("Backdrop.png", sf::IntRect(0,0,512,512)))
        return -1;
    Backdrop.setSmooth(true);
    SetIconBackdrop(Backdrop);

    sf::Texture Texture;
    if (!Texture.loadFromFile("IconPlus.png", sf::IntRect(0,0,512,512)))
    {
        return -1;
    }
    Texture.setSmooth(true);

    sf::Sprite Sprite;
    Sprite.setTexture(Texture);
    Sprite.setOrigin(256, 256);
    Sprite.move(256, 256);

    Block Testblock(Sprite);
    sf::RenderWindow Window(sf::VideoMode(1600, 900), "My window");
    UpdateView(&Window);
    while (Window.isOpen())
    {
        sf::Event Event;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
        {
            dViewingLocation = sf::Vector2f(sf::Mouse::getPosition() - LastMouseLocation);
            ViewingLocation -= dViewingLocation*Zoom;
            UpdateView(&Window);
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
                UpdateView(&Window);
            }
            if (Event.type == sf::Event::Closed)
            {
                Window.close();
            }
            if (Event.type == sf::Event::Resized)
            {
                /*sf::View View(sf::FloatRect(0,0,Event.size.width, Event.size.height));
                View.move(ViewingLocation);
                Window.setView(View);*/
                UpdateView(&Window);
            }
        }
        CollisionCheck(&Window, sf::Vector2f(sf::Mouse::getPosition(Window)), Zoom);
        Window.clear(sf::Color(128, 128, 128));
        BlockDisplayFunc(&Window);
        Window.display();
    }

    return 0;
}
