#pragma once 
#include <SFML/Graphics.hpp>
#include "Screen.h"
#include "sprite/graphics/MeasureSection.h"
#include "sprite/graphics/SelectionRectangle.h"
#include "sprite/core/StateMode.h"
#include <nlohmann/json.hpp>

namespace sprite::graphics
{
    class EditorScreen;
}

std::ostream& operator<<(std::ostream& out, sprite::graphics::EditorScreen& screen);

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
        sf::Font& font;
        core::StateMode& mode;
        std::vector<SelectionRectangle> rects;
        std::string fileName;
        sf::Text saveText;
        sf::Sprite setupSprite(sf::Texture& texture);
        std::vector<SelectionRectangle> setupRects();
        std::vector<SelectionRectangle> setupInitialRects(const nlohmann::json& json);
    public:
        void update() override;
        void reset();
        void manageEvents(const std::optional<sf::Event>& e);
        inline const std::vector<SelectionRectangle>& getRects() const { return rects; }
        inline const MeasureSection& getMeasureSection() const { return measureSection; }
        EditorScreen(
            sf::RenderWindow& window
            , sf::Font& font
            , sf::Texture& texture
            , core::StateMode& mode
            , const nlohmann::json& json
            , const std::string& fileName
        );
        friend std::ostream& ::operator<<(std::ostream& out, EditorScreen& screen);
    };
}
