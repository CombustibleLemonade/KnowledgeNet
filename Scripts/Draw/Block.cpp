#include <iostream>
#include <vector>
#include <math.h>

#include "Block.h"

std::vector<Connector*> AllConnectors;
std::vector<Block*> AllBlocks;
sf::Texture Backdrop;

float AttachmentLength = 128;

sf::Vector2f Interpolate(sf::Vector2f First, sf::Vector2f Last, float Factor)
{
    sf::Vector2f Out = First + (Last - First)*Factor;
    return Out;
}

void Connector::RecalculateVertexArray()
{
    int L = Resolution*2+8;
    Vertices[0] = LeftTarget+sf::Vector2f(-AttachmentLength, 32);
    Vertices[1] = LeftTarget+sf::Vector2f(-AttachmentLength, -32);
    Vertices[0].color = sf::Color(255, 255, 255, 0);
    Vertices[1].color = sf::Color(255, 255, 255, 0);
    Vertices[2] = LeftTarget+sf::Vector2f(0, 32);
    Vertices[3] = LeftTarget+sf::Vector2f(0, -32);
    Vertices[L-4] = RightTarget+sf::Vector2f(0, 32);
    Vertices[L-3] = RightTarget+sf::Vector2f(0, -32);
    Vertices[L-2] = RightTarget+sf::Vector2f(AttachmentLength, 32);
    Vertices[L-1] = RightTarget+sf::Vector2f(AttachmentLength, -32);
    Vertices[L-2].color = sf::Color(255, 255, 255, 0);
    Vertices[L-1].color = sf::Color(255, 255, 255, 0);

    int i = 0;
    while (i<Resolution)
    {
        Vertices[i*2+4] = Interpolate(LeftTarget, RightTarget, i/Resolution)
                + sf::Vector2f(0,32);
        Vertices[i*2+5] = Interpolate(LeftTarget, RightTarget, i/Resolution)
                + sf::Vector2f(0,-32);
        i++;
    }

    PreviousLeftTarget = LeftTarget;
}

Connector::Connector()
{
    AllConnectors.push_back(this);
    Resolution = 30;
    Vertices = sf::VertexArray(sf::TrianglesStrip, Resolution*2+8);
}

void Connector::OnDisplay(sf::RenderWindow * Window)
{
    if(PreviousLeftTarget != LeftTarget)
    {
        RecalculateVertexArray();
    }
    if(PreviousRightTarget != RightTarget)
    {
        RecalculateVertexArray();
    }
    Window->draw(Vertices);
}

void Block::RelocateSprites()
{
    BackdropSprite.setPosition(Position);
    Icon.setPosition(Position);
}

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

Block::Block(sf::String FileLocation)
{
    AllBlocks.push_back(this);
    IconTexture.loadFromFile(FileLocation);
    IconTexture.setSmooth(true);
    Icon.setTexture(IconTexture);
    Icon.setOrigin(256, 256);
    BackdropSprite.setTexture(Backdrop);
    BackdropSprite.setOrigin(256, 256);
    BackdropSprite.setColor(sf::Color(64, 64, 64));

}

void Block::SetPosition(sf::Vector2f SetPosition)
{
    //Connectors[0]->LeftTarget = SetPosition + sf::Vector2f(256, 128);
    Position = SetPosition;
    RelocateSprites();
}

void Block::AddNextBlock(Block *NextBlock)
{
    NextBlocks.push_back(NextBlock);
    NextBlock->PreviousBlocks.push_back(this);

    Connector* NewConnector = new Connector();
    NewConnector->LeftTarget = Position + sf::Vector2f(256, 128);
    NewConnector->RightTarget = NextBlock->Position + sf::Vector2f(-256, 128);
    Connectors.push_back(NewConnector);
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

void BlockDrawFunc(sf::RenderWindow* Window)
{
    int i = 0;
    while (i<AllConnectors.size())
    {
        AllConnectors[i]->OnDisplay(Window);
        i++;
    }
    i = 0;
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

    while (i<AllBlocks.size())
    {
        AllBlocks[i]->CollisionCheck(TrueLocation);
        i++;
    }
}
