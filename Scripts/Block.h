#ifndef BLOCK_DRAWING
#define BLOCK_DRAWING

#include <vector>
#include <SFML/Graphics.hpp>

class Block
{
    std::vector<Block*> PreviousBlocks;
    std::vector<Block*> NextBlocks;

    bool Collision;
    void CollisionFunc();
    void NoCollisionFunc();
public:
    sf::Sprite BackdropSprite;
    sf::Sprite Icon;

    Block();
    Block(sf::Sprite IconToUse);

    void ChangeIcon(sf::Sprite IconToUse);

    void OnDisplay(sf::RenderWindow* Window);
    void AddNextBlock (Block* NextBlock);
    void CollisionCheck(sf::Vector2f Location);
};

void BlockDisplayFunc(sf::RenderWindow* Window);
void SetIconBackdrop(sf::Texture Backdrop);
void CollisionCheck(sf::RenderWindow* Window, sf::Vector2f Location, float Zoom);

#endif
