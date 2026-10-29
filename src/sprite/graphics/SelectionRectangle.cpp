#include "sprite/graphics/SelectionRectangle.h"
#include <sstream>


namespace sprite::graphics
{
    SelectionRectangle::SelectionRectangle()
        : id(getNewId())
        , name(formatInitialName())
        , nameHasChanged{false}
    {
        setOutlineColor(sf::Color(255,0,0,100));
        setFillColor(sf::Color(0,0,0,100));
        setOutlineThickness(2);
    }
    unsigned SelectionRectangle::getNewId()
    {
        static unsigned newId = 0;

        return newId++;
    }
    std::string SelectionRectangle::formatInitialName()
    {
        std::stringstream ss;

        ss << "SpriteFrame" << id;

        return ss.str();
    }
    void SelectionRectangle::setName(const std::string& name)
    {
        nameHasChanged = true;
        SelectionRectangle::name = name;
    }
}