#pragma once 
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "sprite/graphics/MeasureSection.h"
#include "sprite/graphics/SelectionRectangle.h"

namespace sprite::graphics
{
    class EditorScreen : public Screen
    {
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        MeasureSection measureSection;
        sf::RenderWindow& window;
        sf::Sprite sprite;
        unsigned cols, rows;

        std::vector<sprite::graphics::SelectionRectangle> rects;
        sf::Sprite setupSprite(sf::Texture& texture);
        std::vector<sprite::graphics::SelectionRectangle> setupRects();
    public:
        void update() override;
        void manageEvents(const std::optional<sf::Event>& e);
        inline const MeasureSection& getMeasureSection() const { return measureSection; }
        EditorScreen(sf::RenderWindow& window, sf::Font& font, sf::Texture& texture);
    };
}
