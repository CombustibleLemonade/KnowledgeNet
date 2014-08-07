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
    {
        for (i = 0; i ++; i<PageItems.size())
        {
            KNOW::DefaultWindow.draw(PageItems[i]);
        }
    }

    Step::Step()
    {
        BackDrop.setTexture(KNOW::Block::BackdropTex);
    }

    void Step::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        BackDrop.setPosition(getPosition());
        KNOW::CenterOrigin(BackDrop);

        Icon.setPosition(getPosition());

        target.draw(Icon);
        target.draw(BackDrop);

        KNOW::DefaultWindow.draw(PageToDraw);
    }

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
    {
        bool LMBPressed = sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if (LMBPressed)
        {
            OnClick();
            if (!PrevLMBPressed)
            {
                OnClickEntry();
            }
        }
        else if (PrevLMBPressed)
        {
            OnClickExit();
        }
        PrevLMBPressed = LMBPressed;
    }

    void Block::OnClick()
    {}

    void Block::OnClickEntry()
    {
        Selected = true;
    }

    void Block::OnClickExit()
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
        PrevLMBPressed = false;
        Selected = false;
        AllBlocks.push_back(this);
        IconTex.loadFromFile("Block/IconPlus.png");
        IconTex.setSmooth(true);
        Icon.setTexture(IconTex);
        BackdropTex.loadFromFile("Block/Backdrop.png");
        BackdropTex.setSmooth(true);
        Backdrop.setTexture(BackdropTex);

        Step* NewStep = new Step;
        NewStep->setOrigin(0, 0);
        Steps.push_back(NewStep);
    }

    View Block::BlockView;

    void Block::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        Backdrop.setPosition(getPosition());
        KNOW::CenterOrigin(Backdrop);

        Icon.setPosition(getPosition());
        KNOW::CenterOrigin(Icon);

        target.draw(Backdrop);
        target.draw(Icon);
        if (Selected)
        {
            //BlockView.SetTargetPosition(getPosition());
            for(int i = 0; i<Steps.size(); i++)
            {
                target.draw(*Steps[i]);
            }
        }
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
