#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>

namespace sprite::graphics 
{
    class EditorWindow : public sf::RenderWindow
    {
    private:
    
    public:
        EditorWindow(unsigned width, unsigned height, const std::string& title);
    };
}