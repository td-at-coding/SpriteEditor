#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "sprite/graphics/EditorWindow.h"
#include "sprite/graphics/MeasureSection.h"


#ifndef SOURCE_DIR
#define SOURCE_DIR "unknown"
#endif

int main()
{
    sprite::graphics::EditorWindow window(800,600, "SpriteEditor");
    
    sf::Font font;
    if(!font.openFromFile( SOURCE_DIR"/assets/PurisaBold.ttf"))
    {
        // Handle error
        std::cerr << "Failed to load font!" << std::endl;
        return -1;
    }

    sprite::graphics::MeasureSection meaSec(font);

    while (window.isOpen())
    {
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
            else if(const auto* buttonEvent = event->getIf<sf::Event::MouseButtonPressed>())
            {
                auto textBoundOne = meaSec.getGlobalBounds();
                auto textBoundTwo = meaSec.getGlobalBounds();
                textBoundOne.size.x/=2;
                textBoundTwo.position.x += textBoundTwo.size.x/2;
                textBoundTwo.size.x/=2;
                if(buttonEvent->button == sf::Mouse::Button::Left)
                {
                    if(textBoundOne.contains(static_cast<sf::Vector2f>(buttonEvent->position)))
                    {
                        meaSec.increaseColumns();
                    }
                    else if(textBoundTwo.contains(static_cast<sf::Vector2f>(buttonEvent->position)))
                    {
                        meaSec.increaseRows();
                    }
                }
                else if(buttonEvent->button == sf::Mouse::Button::Right)
                {
                    if(textBoundOne.contains(static_cast<sf::Vector2f>(buttonEvent->position)))
                    {
                        meaSec.decreaseColumns();
                    }
                    else if(textBoundTwo.contains(static_cast<sf::Vector2f>(buttonEvent->position)))
                    {
                        meaSec.decreaseRows();
                    }
                }
            }
        }

        window.clear();

        window.draw(meaSec);
        window.display();
    }
    return 0;
}