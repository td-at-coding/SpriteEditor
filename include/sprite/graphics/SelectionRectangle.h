#pragma once
#include <SFML/Graphics.hpp>

namespace sprite::graphics
{
    class SelectionRectangle : public sf::Drawable
    {
    private:
        unsigned id;
        std::string name;
        std::string formatInitialName();
        bool nameHasChanged;
        sf::RectangleShape debugRect;
        sf::Text displayedName;
        bool showText;
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    public:
        SelectionRectangle(sf::Font& font, unsigned id);
        inline unsigned getId() const { return id; }
        inline bool getNameHasChanged() const { return nameHasChanged; }
        inline const std::string& getName() const { return name; }
        void setName(const std::string& name);
        void setPosition(const sf::Vector2f& posVect);
        void setSize(const sf::Vector2f& sizeVect);
        void setupText(const sf::RenderWindow& window);
        inline const sf::RectangleShape& getDebugRectangle() const { return debugRect; }
        inline void setShowText(bool showText) { SelectionRectangle::showText = showText; }
    };
}