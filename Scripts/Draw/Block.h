#ifndef BLOCK_DRAWING
#define BLOCK_DRAWING

#include <SFML/Graphics.hpp>

namespace KNOW
{
    class Page: public sf::Drawable, public sf::Transformable
    {
    public:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };

    class Block: public sf::Drawable, public sf::Transformable
    {
        static sf::Texture BackdropTex;
        mutable sf::Sprite Backdrop;
        sf::Texture IconTex;
        mutable sf::Sprite Icon;

        bool PrevCollide;
        void PrivateCollisionCheck();

        void OnCollision();
        void OnCollisionEntry();
        void OnCollisionExit();
    public:
        static View BlockView;
        std::vector<Page> Pages;
        Block();
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
        static void Draw();
        static void CollisionCheck();
        static void Zoom(int Delta);
    };
}

#endif
