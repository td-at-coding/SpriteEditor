#pragma once
#include <SFML/Graphics.hpp>

namespace sprite::graphics
{
    class SelectionRectangle : public sf::RectangleShape
    {
    private:
        unsigned id;
        std::string name;
        unsigned getNewId();
        std::string formatInitialName();
        bool nameHasChanged;
    public:
        SelectionRectangle();
        inline unsigned getId() const { return id; }
        void setName(const std::string& name);
    };
}