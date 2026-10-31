#include "sprite/graphics/MeasureSection.h"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include "sprite/core/constants.h"
#include <algorithm>
#include <sstream>

namespace sprite::graphics 
{
    // void MeasureSection::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    //     // Apply transform states if your class inherits from sf::Transformable
    //     target.draw(*this, states);
    // }

    MeasureSection::MeasureSection(
        sf::Font& font
        , const nlohmann::json& json
        , const sf::Vector2f& offset
    )
        : sf::Text(font)
        , columnSlices{loadColumns(json)}
        , rowSlices{loadRows(json)}
    {

        std::stringstream ss;

        ss << "Columns: " << columnSlices << " slice(s), Rows: " << rowSlices << " slice(s)";

        setString(ss.str());
        setCharacterSize(18);
        sf::Vector2f SlicesTextPos{0,0};

        setPosition(SlicesTextPos + offset);
    }

    void MeasureSection::resetSlicesText()
    {

        std::stringstream ss;

        ss << "Columns: " << columnSlices << " slice(s), Rows: " << rowSlices << " slice(s)";

        setString(ss.str());
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

    unsigned MeasureSection::loadColumns(const nlohmann::json& json)
    {
        if(not json.empty())
        {
            unsigned value = json["data"]["columns"];
            value = std::clamp(value, core::minColumnSlices, core::maxColumnSlices);
            return value;
        }
        else return 1U;
    }
    unsigned MeasureSection::loadRows(const nlohmann::json& json)
    {
        if(not json.empty())
        {
            unsigned value = json["data"]["rows"];
            value = std::clamp(value, core::minRowSlices, core::maxRowSlices);
            return value;
        }
        else return 1U;
    }
}
