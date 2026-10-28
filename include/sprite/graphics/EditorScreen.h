#pragma once 
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/Window/Event.hpp"
#include "Screen.h"
#include "SFML/Graphics/RenderStates.hpp"
#include "SFML/Graphics/RenderTarget.hpp"
#include "sprite/graphics/MeasureSection.h"

namespace sprite::graphics
{
    class EditorScreen : public Screen
    {
    private:
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        MeasureSection measureSection;
        sf::RenderWindow& window;
    public:
        void update() override;
        void manageEvents(const std::optional<sf::Event>& e);
        inline const MeasureSection& getMeasureSection() const { return measureSection; }
        EditorScreen(sf::RenderWindow& window, sf::Font& font);
    };
}
