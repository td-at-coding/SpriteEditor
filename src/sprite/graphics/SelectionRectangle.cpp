#include "sprite/graphics/SelectionRectangle.h"
#include <sstream>


namespace sprite::graphics
{
    SelectionRectangle::SelectionRectangle(sf::Font& font, unsigned id)
        : id{id}
        , name(formatInitialName())
        , nameHasChanged{false}
        , displayedName{font}
        , showText{false}
    {
        debugRect.setOutlineColor(sf::Color(255,0,0,100));
        debugRect.setFillColor(sf::Color(0,0,0,100));
        debugRect.setOutlineThickness(2);
        displayedName.setFillColor(sf::Color::Green);
        displayedName.setString(name);
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
        displayedName.setString(name);
    }
    void SelectionRectangle::draw(sf::RenderTarget& target, sf::RenderStates states) const 
    {
        target.draw(debugRect, states);
        if(showText)
            target.draw(displayedName, states);
    }

    void SelectionRectangle::setPosition(const sf::Vector2f& posVect)
    {
        debugRect.setPosition(posVect);
    }
    void SelectionRectangle::setSize(const sf::Vector2f& sizeVect)
    {
        debugRect.setSize(sizeVect);
    }
    void SelectionRectangle::setupText(const sf::RenderWindow& window)
    {
        auto rectSize = debugRect.getSize();
        auto windowSize = window.getSize();
        auto rectPos = debugRect.getPosition();
        float ratio = rectSize.y / windowSize.y;
        displayedName.setCharacterSize(ratio * 80);
        auto textSize = displayedName.getGlobalBounds();
        sf::Vector2f textPos{
                rectPos.x+ (rectSize.x - textSize.size.x)/2.0f,
                rectPos.y+ (rectSize.y - textSize.size.y)/2.0f
        };
        displayedName.setPosition(textPos);
    }
}