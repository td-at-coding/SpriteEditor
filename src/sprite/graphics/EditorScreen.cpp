#include "sprite/graphics/EditorScreen.h"
#include "sprite/graphics/MeasureSection.h"
#include <iostream>
#include <TGUI/TGUI.hpp>
#include <fstream>

extern sprite::graphics::SelectionRectangle* rectPtr;
extern tgui::EditBox::Ptr editBox;

namespace sprite::graphics 
{
    void EditorScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const 
    {
        target.draw(measureSection, states);
        target.draw(saveText, states);
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
                else if(saveText.getGlobalBounds().contains(static_cast<sf::Vector2f>(mouseEvent->position)))
                {
                    std::string jsonFile = fileName +".json";
                    std::ofstream f(jsonFile);
                    f << *this;
                    f.close();

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
        , const nlohmann::json& json
        , const std::string& fileName
    )
        : window(window)
        , measureSection(font, json)
        , sprite{setupSprite(texture)}
        , rects(setupInitialRects(json))
        , cols{measureSection.getColumnSlices()}
        , rows{measureSection.getRowSlices()}
        , font{font}
        , mode{mode}
        , fileName{fileName}
        , saveText{font}
    {
        saveText.setString("Save");
        saveText.setCharacterSize(18U);
        auto textSize = saveText.getGlobalBounds();
        auto windowSize = window.getSize();
        sf::Vector2f textPos{windowSize.x - textSize.size.x, 0};
        saveText.setPosition(textPos);
    }

    std::vector<SelectionRectangle> EditorScreen::setupInitialRects(const nlohmann::json& json)
    {
        std::vector<SelectionRectangle> rects = setupRects();
        if(not json.empty())
        {
            for(const auto& sprite : json["data"]["sprites"])
            {
                for(const auto& id : sprite["ids"])
                    rects[id].setName(sprite["name"]);
            }
            return rects;
        }
        else return rects;
    }

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

    std::vector<SelectionRectangle> EditorScreen::setupRects()
    {
        auto meaSecBounds = measureSection.getGlobalBounds();
        auto windowSize = window.getSize();
        float target_width =windowSize.x;
        float target_height = windowSize.y - meaSecBounds.size.y;

        int cols = measureSection.getColumnSlices();
        int rows = measureSection.getRowSlices();
        std::vector<SelectionRectangle> rects;
        unsigned idx = 0;
        for(int i = 0; i < rows; i++)
        {
            for(int j = 0; j < cols; j++)
            {
                SelectionRectangle rect(font, idx);
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

std::ostream& operator<<(std::ostream& out, sprite::graphics::EditorScreen& screen)
{
    nlohmann::json json;
    json["data"] = nlohmann::json::object();
    json["data"]["columns"] = screen.getMeasureSection().getColumnSlices();
    json["data"]["rows"] = screen.getMeasureSection().getRowSlices();

    std::unordered_map<std::string, std::vector<unsigned>> map;
    for(const auto& rect : screen.getRects())
    {
        if(rect.getNameHasChanged())
        {
            map[rect.getName()].push_back(rect.getId());
        }
    }
    json["data"]["sprites"] = nlohmann::json::array();
    for(const auto& p : map)
    {
        nlohmann::json jObject;
        jObject["name"] = p.first;
        jObject["ids"] = p.second;
        json["data"]["sprites"].push_back(jObject);
    }

    out << json;

    return out;
}