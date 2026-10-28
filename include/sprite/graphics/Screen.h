#pragma once
#include "SFML/Graphics/Drawable.hpp"

namespace sprite::graphics
{
    class Screen : public sf::Drawable
    {
    protected:
    public:
        virtual void update() = 0;
    };

}
