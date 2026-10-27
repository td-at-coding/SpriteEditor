#include "sprite/graphics/MeasureSection.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "SFML/System/Vector2.hpp"
#include "sprite/core/constants.h"
#include <algorithm>
#include <sstream>

namespace sprite::graphics 
{
    void MeasureSection::draw(sf::RenderTarget& target, sf::RenderStates states) const {
        // Apply transform states if your class inherits from sf::Transformable
        target.draw(SlicesText, states);
    }

    MeasureSection::MeasureSection(sf::Font& font, const sf::Vector2f& offset)
        : SlicesText(font)
        , columnSlices(1)
        , rowSlices(1)
    {

        std::stringstream ss;

        ss << "Columns: " << columnSlices << " slice(s), Rows: " << rowSlices << " slice(s)";

        SlicesText.setString(ss.str());
        SlicesText.setCharacterSize(18);
        sf::Vector2f SlicesTextPos{0,0};

        SlicesText.setPosition(SlicesTextPos + offset);
    }

    void MeasureSection::resetSlicesText()
    {

        std::stringstream ss;

        ss << "Columns: " << columnSlices << " slice(s), Rows: " << rowSlices << " slice(s)";

        SlicesText.setString(ss.str());
    }

    void MeasureSection::increaseColumns()
    {
        columnSlices = std::min(columnSlices+1, core::maxColumnSlices);
        resetSlicesText();
    }
    void MeasureSection::increaseRows()
    {
        rowSlices = std::min(rowSlices+1, core::maxRowSlices);
        resetSlicesText();
    }
    void MeasureSection::decreaseColumns()
    {
        columnSlices = std::max(columnSlices-1, core::minColumnSlices);
        resetSlicesText();
    }
    void MeasureSection::decreaseRows()
    {
        rowSlices = std::max(rowSlices-1, core::minRowSlices);
        resetSlicesText();
    }
}
