#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "sprite/graphics/EditorScreen.h"
#include "sprite/graphics/EditorWindow.h"
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>
#include "sprite/graphics/SelectionRectangle.h"
#include "sprite/core/StateMode.h"

#ifndef SOURCE_DIR
#define SOURCE_DIR "unknown"
#endif


sprite::graphics::SelectionRectangle* rectPtr{nullptr};
tgui::EditBox::Ptr editBox;

int main(int argc, char* argv[])
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

    sprite::core::StateMode mode{sprite::core::TEXT_EDIT};


    //SFML
    sprite::graphics::EditorScreen* screen{nullptr};

    
    //TGUI

    tgui::Gui gui{window};

    editBox = tgui::EditBox::create();
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
            rectPtr->setupText(window);
        }
        mode = sprite::core::SCREEN_EDITOR;
        std::cout << "Current text: " << text.toStdString() << std::endl;
    });

    auto openFileDialog = tgui::FileDialog::create("Open An Image", "Open");
    openFileDialog->setPath(argv[0]);
    openFileDialog->setFileTypeFilters({ {"Images", {"*.png", "*.jpg"}} });
    
    auto dialogSize = openFileDialog->getSize();
    auto windowSize = window.getSize();
    tgui::Vector2f dialogPosition{(windowSize.x - dialogSize.x)/2.0f, (windowSize.y - dialogSize.y)/2.0f};
    
    openFileDialog->setPosition(dialogPosition);

    gui.add(openFileDialog);
    
    sf::Texture texture;
    openFileDialog->onFileSelect([&](const tgui::Filesystem::Path& path)
    {
        if(not texture.loadFromFile(path.asString().toStdString()))
        {
            // Handle error
            std::cerr << "Failed to load texture!" << std::endl;
            exit(-1);
        }
        screen = new sprite::graphics::EditorScreen(window, font, texture, mode);
    });

    while (window.isOpen())
    {
        switch(mode)
        {
        case sprite::core::SCREEN_EDITOR:
        {
            if(screen)
                screen->update();
            else 
                return 1;
            break;
        }
        case sprite::core::TEXT_EDIT:
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
        if(screen)
        {
            window.draw(*screen);
            screen->reset();
        }

        if(mode == sprite::core::TEXT_EDIT)
        {
            gui.draw();
        }

        window.display();
    }
    if(screen)
    {
        delete screen;
        screen = nullptr;
    }
    return 0;
}