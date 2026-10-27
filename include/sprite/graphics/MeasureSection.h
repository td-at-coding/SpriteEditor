#pragma once 

#include "SFML/Graphics/Drawable.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"

namespace sprite::graphics
{
class MeasureSection : public sf::Drawable 
{
private:
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    sf::Text columnsSliceText, rowsSliceText;
public:
    MeasureSection(sf::Font& font, const sf::Vector2f& offset={0,0});
};

}