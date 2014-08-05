#ifndef BLOCK_DRAWING
#define BLOCK_DRAWING

#include <SFML/Graphics.hpp>

namespace KNOW
{
    class PageItem: public sf::Drawable, public sf::Transformable
    {};

    class PageItemText: public PageItem
    {
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

    class Page: public sf::Drawable, public sf::Transformable
    {
        std::vector<PageItem> PageItems;
    public:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

    class Step: public sf::Drawable, public sf::Transformable
    {
        mutable sf::Sprite BackDrop;
        sf::View StepView;
    public:
        Step();

        sf::Texture* IconTex;
        mutable sf::Sprite Icon;
        Page PageToDraw;
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

    class Block: public sf::Drawable, public sf::Transformable
    {
        mutable sf::Sprite Backdrop;
        sf::Texture IconTex;
        mutable sf::Sprite Icon;

        bool PrevCollide;
        void PrivateCollisionCheck();

        bool PrevLMBPressed;
        void OnCollision();
        void OnCollisionEntry();
        void OnCollisionExit();

        void OnClick();
        void OnClickEntry();
        void OnClickExit();
        bool Selected;
    public:
        static sf::Texture BackdropTex;

        static View BlockView;
        std::vector<Step*> Steps;
        Block();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        static void Draw();
        static void CollisionCheck();
        static void Zoom(int Delta);
    };
}

#endif
