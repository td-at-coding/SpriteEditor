#include "sprite/graphics/EditorScreen.h"
#include "sprite/graphics/MeasureSection.h"
#include <iostream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

extern sprite::graphics::SelectionRectangle* rectPtr;
extern tgui::EditBox::Ptr editBox;

namespace sprite::graphics 
{
    void EditorScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const 
    {
        target.draw(measureSection, states);
        target.draw(sprite, states);
        for(const auto& rect : rects)
        {
            target.draw(rect, states);
        }
    }

    void EditorScreen::update()
    {
        while (auto event = window.pollEvent())
        {
            manageEvents(event);
        }

        if(cols != measureSection.getColumnSlices() or rows != measureSection.getRowSlices())
        {
            rects = setupRects();
            cols = measureSection.getColumnSlices();
            rows = measureSection.getRowSlices();
        }
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);
        for(auto& rect : rects)
        {
            if(rect.getDebugRectangle().getGlobalBounds().contains(static_cast<sf::Vector2f>(localPosition)))
            {
                rect.setShowText(true);
            }
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

                for(auto& rect : rects)
                {
                    if(rect.getDebugRectangle().getGlobalBounds().contains(static_cast<sf::Vector2f>(mouseEvent->position)))
                    {
                        mode = core::TEXT_EDIT;
                        rectPtr = &rect;
                        editBox->setText(rect.getName());
                    }
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
    EditorScreen::EditorScreen(
        sf::RenderWindow& window
        , sf::Font& font
        , sf::Texture& texture
        , core::StateMode& mode
    )
        : window(window)
        , measureSection(font)
        , sprite{setupSprite(texture)}
        , rects(setupRects())
        , cols{measureSection.getColumnSlices()}
        , rows{measureSection.getRowSlices()}
        , font{font}
        , mode{mode}
    {}

    sf::Sprite EditorScreen::setupSprite(sf::Texture& texture)
    {
        sf::Vector2u textureSize = texture.getSize();
        auto meaSecBounds = measureSection.getGlobalBounds();
        auto windowSize = window.getSize();
        sf::Sprite sprite{texture};
        float target_width =windowSize.x;
        float target_height = windowSize.y - meaSecBounds.size.y;

        float scaleX = target_width / static_cast<float>(textureSize.x);
        float scaleY = target_height / static_cast<float>(textureSize.y);

        sprite.setScale({
            scaleX
            , scaleY
        });

        sprite.setPosition({0.f, meaSecBounds.size.y});
        return sprite;
    }

    std::vector<sprite::graphics::SelectionRectangle> EditorScreen::setupRects()
    {
        auto meaSecBounds = measureSection.getGlobalBounds();
        auto windowSize = window.getSize();
        float target_width =windowSize.x;
        float target_height = windowSize.y - meaSecBounds.size.y;

        int cols = measureSection.getColumnSlices();
        int rows = measureSection.getRowSlices();
        std::vector<sprite::graphics::SelectionRectangle> rects;
        unsigned idx = 0;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                sprite::graphics::SelectionRectangle rect(font, idx);
                sf::Vector2f rectSize{target_width / (float)cols-2, target_height / (float)rows-2};
                sf::Vector2f rectPosition{1+j*rectSize.x, 1+meaSecBounds.size.y+i*rectSize.y};
                rect.setSize(rectSize);
                rect.setPosition(rectPosition);
                rect.setupText(window);
                rects.push_back(rect);
                idx++;
            }
        }
        return rects;
    }
    void EditorScreen::reset()
    {
        for(auto& rect : rects)
        {
            rect.setShowText(false);
        }
    }
}