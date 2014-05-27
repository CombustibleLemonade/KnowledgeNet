#include <iostream>
#include <vector>

#include "Block.h"

std::vector<Block*> AllBlocks;
sf::Texture Backdrop;

class Connector {
public:
    float PreviousHeight;
    float NextHeight;
    Block* Previous;
    Block* Next;
};

void Block::CollisionFunc()
{
    BackdropSprite.setColor(sf::Color(128, 128, 255));
    BackdropSprite.setScale(1.1, 1.1);
    Collision = true;
}

void Block::NoCollisionFunc()
{
    BackdropSprite.setColor(sf::Color(64, 64, 64));
    BackdropSprite.setScale(1.0, 1.0);
    Collision = false;
}

Block::Block ()
{
    AllBlocks.push_back(this);
}

Block::Block(sf::Sprite IconToUse)
{
    AllBlocks.push_back(this);
    Icon = IconToUse;
    BackdropSprite.setTexture(Backdrop);
    BackdropSprite.setPosition(Icon.getPosition());
    BackdropSprite.setOrigin(256, 256);
    BackdropSprite.setColor(sf::Color(64, 64, 64));
}

void Block::AddNextBlock(Block *NextBlock)
{
    NextBlocks.push_back(NextBlock);
    NextBlock->PreviousBlocks.push_back(this);
}

void Block::OnDisplay(sf::RenderWindow* Window)
{
    Window->draw(BackdropSprite);
    Window->draw(Icon);
}

void Block::CollisionCheck(sf::Vector2f Location)
{
    bool DoesCollide = true;
    DoesCollide &= Icon.getGlobalBounds().left<Location.x;
    DoesCollide &= Icon.getGlobalBounds().left +Icon.getGlobalBounds().width>Location.x;
    DoesCollide &= -Icon.getGlobalBounds().top>Location.y;
    DoesCollide &= -Icon.getGlobalBounds().top-Icon.getGlobalBounds().height<Location.y;
    if (DoesCollide)
        CollisionFunc();
    else if (Collision)
        NoCollisionFunc();

}

void BlockDisplayFunc(sf::RenderWindow* Window)
{
    int i = 0;
    while (i<AllBlocks.size())
    {
        AllBlocks[i]->OnDisplay(Window);
        i++;
    }
}

void SetIconBackdrop(sf::Texture NewBackdrop) {
    Backdrop = NewBackdrop;
}

void CollisionCheck(sf::RenderWindow* Window, sf::Vector2f Location, float Zoom)
{
    int i = 0;
    sf::Vector2f TrueLocation = (Location -
                                 (sf::Vector2f(Window->getSize())/2.0f))*Zoom;
    TrueLocation += sf::Vector2f(Window->getView().getCenter());
    TrueLocation.y = - TrueLocation.y;

    //std::cout << "x: " << TrueLocation.x << " y: " << TrueLocation.y << std::endl;
    while (i<AllBlocks.size())
    {
        AllBlocks[i]->CollisionCheck(TrueLocation);
        i++;
    }
}
