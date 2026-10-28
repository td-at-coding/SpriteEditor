#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <iostream>
#include "sprite/graphics/EditorScreen.h"
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

    sprite::graphics::EditorScreen screen(window, font);

    while (window.isOpen())
    {
        screen.update();

        window.clear();

        window.draw(screen);
        window.display();
    }
    return 0;
}