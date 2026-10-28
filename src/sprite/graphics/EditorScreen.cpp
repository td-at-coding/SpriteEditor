#include "sprite/graphics/EditorScreen.h"
#include "sprite/graphics/MeasureSection.h"

namespace sprite::graphics 
{
    void EditorScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const 
    {
        target.draw(measureSection, states);
    }

    void EditorScreen::update()
    {
        while (auto event = window.pollEvent())
        {
            manageEvents(event);
        }
    }

    void EditorScreen::manageEvents(const std::optional<sf::Event>& e)
    {

        if (e->is<sf::Event::Closed>())
            window.close();
        else if(const auto* mouseEvent = e->getIf<sf::Event::MouseButtonPressed>())
        {
            auto textBoundOne = measureSection.getGlobalBounds();
            auto textBoundTwo = measureSection.getGlobalBounds();
            textBoundOne.size.x/=2;
            textBoundTwo.position.x += textBoundTwo.size.x/2;
            textBoundTwo.size.x/=2;
            if(mouseEvent->button == sf::Mouse::Button::Left)
            {
                if(textBoundOne.contains(static_cast<sf::Vector2f>(mouseEvent->position)))
                {
                    measureSection.increaseColumns();
                }
                else if(textBoundTwo.contains(static_cast<sf::Vector2f>(mouseEvent->position)))
                {
                    measureSection.increaseRows();
                }
            }
            else if(mouseEvent->button == sf::Mouse::Button::Right)
            {
                if(textBoundOne.contains(static_cast<sf::Vector2f>(mouseEvent->position)))
                {
                    measureSection.decreaseColumns();
                }
                else if(textBoundTwo.contains(static_cast<sf::Vector2f>(mouseEvent->position)))
                {
                    measureSection.decreaseRows();
                }
            }
        }
    }
    EditorScreen::EditorScreen(sf::RenderWindow& window, sf::Font& font)
        : window(window)
        , measureSection(font)
    {}
}