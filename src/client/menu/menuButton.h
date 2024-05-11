#ifndef MENUBUTTON_H
#define MENUBUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class MenuButton {
public:
    MenuButton(const sf::Vector2f& position, const std::string& text, const sf::Font& font, unsigned int characterSize = 30,
               sf::Color textColor = sf::Color::White, sf::Color buttonColor = sf::Color::Blue, 
               sf::Color hoverColor = sf::Color::Cyan, float width = 150.f, float height = 50.f);

    void draw(sf::RenderWindow& window);

    bool isMouseOver(const sf::RenderWindow& window) const;
    bool isPressed(const sf::RenderWindow& window) const; // Check if pressed in current frame

    void setSize(float width, float height);
    void setButtonColor(const sf::Color& color);
    void setHoverColor(const sf::Color& color);


private:
    sf::RectangleShape button;
    sf::Text textObj;
    sf::Color buttonColor;
    sf::Color hoverColor;
    bool isPressedInCurrentFrame = false;
};

#endif