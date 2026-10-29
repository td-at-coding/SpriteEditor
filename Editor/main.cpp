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
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include <sprite/graphics/SelectionRectangle.h>


#ifndef SOURCE_DIR
#define SOURCE_DIR "unknown"
#endif



enum StateMode
{
    SCREEN_EDITOR,
    TEXT_EDIT
};


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

    StateMode mode{TEXT_EDIT};
    sprite::graphics::SelectionRectangle* rectPtr{nullptr};

    //TGUI

    tgui::Gui gui{window};

    auto editBox = tgui::EditBox::create();
    editBox->setSize(300, 40);
    editBox->setPosition(250, 200);
    editBox->setDefaultText("Click here to type...");
    editBox->setTextSize(16);
    editBox->getRenderer()->setBackgroundColor(tgui::Color::Red);

    gui.add(editBox);

    editBox->onReturnKeyPress([&](const tgui::String& text) {
        if(rectPtr)
        {
            rectPtr->setName(text.toStdString());
        }
        mode = SCREEN_EDITOR;
        std::cout << "Current text: " << text.toStdString() << std::endl;
    });

    //SFML
    sprite::graphics::EditorScreen screen(window, font, player_texture);

    while (window.isOpen())
    {
        switch(mode)
        {
        case SCREEN_EDITOR:
        {
            screen.update();
            break;
        }
        case TEXT_EDIT:
        {
            while (auto e = window.pollEvent())
            {
                gui.handleEvent(e.value());
                if (e->is<sf::Event::Closed>())
                    window.close();
            }
            break;
        }
        }

        window.clear();

        window.draw(screen);

        if(mode == TEXT_EDIT)
        {
            gui.draw();
        }

        window.display();
    }
    return 0;
}