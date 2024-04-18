#ifndef TEXTFIELD_H
#define TEXTFIELD_H

#include <SFML/Graphics.hpp>
#include <string>

class Textfield
{
public:
    Textfield(const sf::Vector2f& location, const std::string& text, const sf::Font& font, unsigned int characterSize, sf::Color textColor, sf::Color backgroundColor, float width, float height);

    void draw(sf::RenderWindow& window) const;

    void setText(const std::string& newText);
    std::string getText() const;

    void setPosition(const sf::Vector2f& newLocation);
    sf::Vector2f getPosition() const;

    bool isMouseOver(const sf::RenderWindow& window) const;

    bool isActive() const { return active; }
    void setActive(bool active);

    void handleInput(const sf::Event& event);
    void update(const sf::Time& deltaTime);

    void setBackgroundColor(const sf::Color& color);

    std::string text;
    sf::Text textObj; 


protected:
    sf::RectangleShape background;

private:
    sf::Vector2f location;
    sf::Font font; 
    unsigned int characterSize;
    sf::Color textColor;
    bool active=false;
    sf::RectangleShape cursor;
    sf::Time elapsedTime;
    bool showCursor=true;
};

#endif