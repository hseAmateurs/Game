#include "MenuButton.h"

MenuButton::MenuButton(const sf::Vector2f& position, const std::string& text, const sf::Font& font, unsigned int characterSize,
                       sf::Color textColor, sf::Color buttonColor, sf::Color hoverColor, float width, float height) :
    buttonColor(buttonColor),
    hoverColor(hoverColor)
{
    button.setPosition(position);
    button.setSize(sf::Vector2f(width, height));
    button.setFillColor(buttonColor);

    textObj.setFont(font);
    textObj.setString(text);
    textObj.setCharacterSize(characterSize);
    textObj.setFillColor(textColor);

    // Center the text within the button
    sf::FloatRect textBounds = textObj.getLocalBounds();
    textObj.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    textObj.setPosition(button.getPosition() + sf::Vector2f(width / 2.f, height / 2.f)); 
}

void MenuButton::setSize(float width, float height) {
    button.setSize(sf::Vector2f(width, height));

    // Recenter the text after changing the button size
    sf::FloatRect textBounds = textObj.getLocalBounds();
    textObj.setOrigin(textBounds.left + textBounds.width / 2.f, textBounds.top + textBounds.height / 2.f);
    textObj.setPosition(button.getPosition() + sf::Vector2f(width / 2.f, height / 2.f)); 
}

void MenuButton::setButtonColor(const sf::Color& color) {
    buttonColor = color;
    button.setFillColor(buttonColor);
}

void MenuButton::setHoverColor(const sf::Color& color) {
    hoverColor = color;
}

bool MenuButton::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return button.getGlobalBounds().contains(mousePos.x, mousePos.y);
}

void MenuButton::draw(sf::RenderWindow& window){
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if(button.getGlobalBounds().contains(mousePos.x, mousePos.y)){
        button.setFillColor(hoverColor);
    }
    else{
        button.setFillColor(buttonColor);
    }
    window.draw(button);
    window.draw(textObj);
}

bool MenuButton::isPressed(const sf::RenderWindow& window) const {
    // Check if mouse is over and left button is pressed
    return isMouseOver(window) && sf::Mouse::isButtonPressed(sf::Mouse::Left); 
}