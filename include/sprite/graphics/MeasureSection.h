#pragma once 

#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Text.hpp"
#include "SFML/System/Vector2.hpp"
#include <nlohmann/json.hpp>

namespace sprite::graphics
{
class MeasureSection : public sf::Text 
{
private:
    unsigned columnSlices, rowSlices;
public:
    MeasureSection(sf::Font& font,const nlohmann::json& json, const sf::Vector2f& offset={0,0});

    unsigned loadColumns(const nlohmann::json& json);
    unsigned loadRows(const nlohmann::json& json);
    void resetSlicesText();
    void increaseColumns();
    void increaseRows();
    void decreaseColumns();
    void decreaseRows();
    inline unsigned getColumnSlices() const {return columnSlices; }
    inline unsigned getRowSlices() const {return rowSlices; }
};

}