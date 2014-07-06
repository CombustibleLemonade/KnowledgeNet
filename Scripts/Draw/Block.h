#ifndef BLOCK_DRAWING
#define BLOCK_DRAWING

#include <SFML/Graphics.hpp>

namespace KNOW
{
    class Block: public sf::Drawable, public sf::Transformable
    {
        sf::Texture Texture;
        mutable sf::Sprite Icon;
    public:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    };
}

#endif
