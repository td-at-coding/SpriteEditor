#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include <vector>
#include "sprite/graphics/EditorScreen.h"
#include "sprite/graphics/EditorWindow.h"


#ifndef SOURCE_DIR
#define SOURCE_DIR "unknown"
#endif

int main()
{
    sprite::graphics::EditorWindow window(800,600, "SpriteEditor");
    
    sf::Font font;
    if(not font.openFromFile( SOURCE_DIR"/assets/PurisaBold.ttf"))
    {
        // Handle error
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }
    sf::Texture player_texture;

    if(not player_texture.loadFromFile(SOURCE_DIR"/assets/player_sprites.png"))
    {
        // Handle error
        std::cerr << "Failed to load texture!" << std::endl;
        return -1;
    }

    sf::Vector2u textureSize = player_texture.getSize();
    
    sprite::graphics::EditorScreen screen(window, font);
    auto meaSecBounds = screen.getMeasureSection().getGlobalBounds();
    auto windowSize = window.getSize();
    sf::Sprite sprite{player_texture};
    float target_width =windowSize.x;
    float target_height = windowSize.y - meaSecBounds.size.y;

    float scaleX = target_width / static_cast<float>(textureSize.x);
    float scaleY = target_height / static_cast<float>(textureSize.y);

    sprite.setScale({
        scaleX
        , scaleY
    });


    sprite.setPosition({0.f, meaSecBounds.size.y});
    const auto& meaSec = screen.getMeasureSection();
    int cols = meaSec.getColumnSlices();
    int rows = meaSec.getRowSlices();
    std::cout << "Cols: " << cols << ", Rows: " << rows << std::endl;
    std::cout << "Width: " << target_width << ", Height: " << target_height << std::endl;
    std::vector<sf::RectangleShape> rects;

    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < cols; j++)
        {
            sf::RectangleShape rect;
            sf::Vector2f rectSize{target_width / (float)cols-2, target_height / (float)rows-2};
            sf::Vector2f rectPosition{1+j*rectSize.x, 1+meaSecBounds.size.y+i*rectSize.y};
            rect.setSize(rectSize);
            rect.setPosition(rectPosition);
            rect.setOutlineColor(sf::Color(255,0,0,100));
            rect.setFillColor(sf::Color(0,0,0,100));
            rect.setOutlineThickness(2);
            rects.push_back(rect);
        }
    }

    while (window.isOpen())
    {
        screen.update();
        if(cols != meaSec.getColumnSlices() or rows != meaSec.getRowSlices())
        {
            rects.clear();
            cols = meaSec.getColumnSlices();
            rows = meaSec.getRowSlices();
            for(int i = 0; i < rows; i++)
            {
                for(int j = 0; j < cols; j++)
                {
                    sf::RectangleShape rect;
                    sf::Vector2f rectSize{target_width / (float)cols-2, target_height / (float)rows-2};
                    sf::Vector2f rectPosition{1+j*rectSize.x, 1+meaSecBounds.size.y+i*rectSize.y};
                    rect.setSize(rectSize);
                    rect.setPosition(rectPosition);
                    rect.setOutlineColor(sf::Color(255,0,0,100));
                    rect.setFillColor(sf::Color(0,0,0,100));
                    rect.setOutlineThickness(2);
                    rects.push_back(rect);
                }
            }
        }

        window.clear();

        window.draw(screen);
        window.draw(sprite);
        for(int i = 0; i < rects.size(); i++)
        {
            window.draw(rects[i]);
        }
        window.display();
    }
    return 0;
}