#include "Base/Defaults.h"
#include "Base/Base.h"
#include "Block.h"

#include <iostream>

std::vector<KNOW::Block*> AllBlocks;

bool PrevClick = false;
sf::Vector2f MouseStartPosition;
sf::Vector2f PrevViewCenter;

int i = 0;

namespace KNOW
{
    void Page::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {}

    sf::Texture Block::BackdropTex;

    void Block::PrivateCollisionCheck()
    {
        bool Collide = KNOW::CursorCollisionCheck(Backdrop.getGlobalBounds(), BlockView.ZoomValue);
        if (Collide)
        {
            if (!PrevCollide)
            {
                OnCollisionEntry();
            }
            OnCollision();
        }
        else if (PrevCollide)
        {
            OnCollisionExit();
        }
        PrevCollide = Collide;
    }

    void Block::OnCollision()
    {}

    void Block::OnCollisionEntry()
    {
        Backdrop.setColor(sf::Color(0, 255, 0));
        Backdrop.setScale(1.1, 1.1);
    }

    void Block::OnCollisionExit()
    {
        Backdrop.setColor(sf::Color(255, 255, 255));
        Backdrop.setScale(1.0, 1.0);
    }

    Block::Block()
    {
        PrevCollide = false;
        AllBlocks.push_back(this);
        IconTex.loadFromFile("Block/IconPlus.png");
        IconTex.setSmooth(true);
        Icon.setTexture(IconTex);
        BackdropTex.loadFromFile("Block/Backdrop.png");
        BackdropTex.setSmooth(true);
        Backdrop.setTexture(BackdropTex);
    }

    View Block::BlockView;

    void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        Backdrop.setPosition(getPosition());
        sf::FloatRect IconRect = Backdrop.getLocalBounds();
        sf::Vector2f Displace = sf::Vector2f(IconRect.width/2, IconRect.height/2);
        Backdrop.setOrigin(Displace);


        Icon.setPosition(getPosition());
        IconRect = Icon.getLocalBounds();
        Displace = sf::Vector2f(IconRect.width/2, IconRect.height/2);
        Icon.setOrigin(Displace);

        target.draw(Backdrop);
        target.draw(Icon);
    }

    void Block::Draw()
    {
        i = 0;
        Block::BlockView.AdjustToScreenRes();
        KNOW::DefaultWindow.setView(Block::BlockView);
        for(int i = 0; i < AllBlocks.size(); i++){
            KNOW::DefaultWindow.draw(*AllBlocks[i]);
        }
    }

    void Block::CollisionCheck()
    {
        sf::Vector2f MousePosition = sf::Vector2f(sf::Mouse::getPosition(KNOW::DefaultWindow));
        bool IsButtonPressed = sf::Mouse::isButtonPressed(sf::Mouse::Middle);
        if (IsButtonPressed)
        {
            if (!PrevClick)
            {
                MouseStartPosition = MousePosition;
                PrevViewCenter = Block::BlockView.getCenter();
            }
            sf::Vector2f Delta = (MousePosition - MouseStartPosition)*Block::BlockView.ZoomValue;
            Block::BlockView.setCenter(PrevViewCenter - Delta);
        }
        PrevClick = sf::Mouse::isButtonPressed(sf::Mouse::Middle);
        for(int i = 0; i < AllBlocks.size(); i++){
            AllBlocks[i]->PrivateCollisionCheck();
        }
    }

    void Block::Zoom(int Delta)
    {
        if (Delta == 1)
        {
            BlockView.ZoomValue /= 1.2;
        }
        else
        {
            BlockView.ZoomValue *= 1.2;
        }
    }

    Block newBlock;
}
