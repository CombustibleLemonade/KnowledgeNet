#ifndef BLOCK_DRAWING
#define BLOCK_DRAWING

#include <vector>
#include <SFML/Graphics.hpp>

class Connector {
    void RecalculateVertexArray();
    sf::VertexArray Vertices;

    sf::Vector2f PreviousLeftTarget;
    sf::Vector2f PreviousRightTarget;
public:
    Connector();

    sf::Vector2f LeftTarget;
    sf::Vector2f RightTarget;

    float Resolution;

    void OnDisplay(sf::RenderWindow * Window);
};

class Block
{
    void RelocateSprites();
    std::vector<Block*> PreviousBlocks;
    std::vector<Block*> NextBlocks;
    std::vector<Connector*> Connectors;

    bool Collision;
    void CollisionFunc();
    void NoCollisionFunc();

    sf::Vector2f Position;

    sf::Texture IconTexture;
    sf::Sprite BackdropSprite;
    sf::Sprite Icon;
public:
    Block();
    Block(sf::String FileLocation);

    void SetPosition(sf::Vector2f SetPosition);
    void Move(sf::Vector2f DeltaPosition);

    void ChangeIcon(sf::Sprite IconToUse);

    void OnDisplay(sf::RenderWindow* Window);
    void AddNextBlock (Block* NextBlock);
    void CollisionCheck(sf::Vector2f Location);
};

void BlockDrawFunc(sf::RenderWindow* Window);
void SetIconBackdrop(sf::Texture Backdrop);
void CollisionCheck(PointOfView* POV, sf::Vector2f Location, float Zoom);

#endif
