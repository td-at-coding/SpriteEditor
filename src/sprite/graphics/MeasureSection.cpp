#include "sprite/graphics/MeasureSection.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"

namespace sprite::graphics 
{
void MeasureSection::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // Apply transform states if your class inherits from sf::Transformable
    target.draw(columnsSliceText, states);
    target.draw(rowsSliceText, states);
}

MeasureSection::MeasureSection(sf::Font& font, const sf::Vector2f& offset)
    : columnsSliceText(font), rowsSliceText(font)
{

    columnsSliceText.setString("RowsSlice: ");
    columnsSliceText.setCharacterSize(18);
    sf::Vector2f columnsSliceTextPos{0,0};

    columnsSliceText.setPosition(columnsSliceTextPos + offset);
}

}
