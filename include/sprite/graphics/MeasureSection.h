#pragma once 

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"

namespace sprite::graphics
{
class MeasureSection : public sf::Text 
{
private:
    unsigned columnSlices, rowSlices;
public:
    MeasureSection(sf::Font& font, const sf::Vector2f& offset={0,0});

    void resetSlicesText();
    void increaseColumns();
    void increaseRows();
    void decreaseColumns();
    void decreaseRows();
};

}