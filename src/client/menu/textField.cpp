#include "textField.h"

Textfield::Textfield(const sf::Vector2f& location, const std::string& text, const sf::Font& font, unsigned int characterSize, sf::Color textColor, sf::Color backgroundColor, float width, float height) :
    location(location),
    text(text),
    font(font),
    characterSize(characterSize),
    textColor(textColor)
{
    textObj.setFont(font);
    textObj.setString(text);
    textObj.setCharacterSize(characterSize);
    textObj.setFillColor(textColor);
    textObj.setPosition(location+sf::Vector2f(4.f,height-textObj.getLocalBounds().top+textObj.getLocalBounds().height-35.f));
    cursor.setSize(sf::Vector2f(2.f, characterSize)); // Adjust cursor width as needed
    cursor.setFillColor(textColor);
    background.setPosition(location);
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(backgroundColor);
}

bool Textfield::isMouseOver(const sf::RenderWindow& window) const {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return background.getGlobalBounds().contains(mousePos.x, mousePos.y);
}


void Textfield::setBackgroundColor(const sf::Color& color){
    background.setFillColor(color);
}

void Textfield::setActive(bool active) {
    this->active = active; 
    if (active) {
        elapsedTime = sf::Time::Zero; // Reset blink timer when activated
        showCursor = true; // Show cursor initially
    }
}

void Textfield::handleInput(const sf::Event& event) {
    if (!active) return; // Ignore input if not active

    if (event.type == sf::Event::TextEntered) {
        // Handle text input (add characters, backspace, etc.)
        if (event.text.unicode == '\b' && !text.empty()) {
            text.pop_back();
        } else if (event.text.unicode == ' ' || (event.text.unicode == '\b' && text.empty())) {
    
        }
        else{
            text+=event.text.unicode;
        }
        textObj.setString(text);
    }
}

void Textfield::update(const sf::Time& deltaTime) {
    if (!active) return; 

    // Cursor blinking logic
    elapsedTime += deltaTime;
    if (elapsedTime >= sf::seconds(0.5f)) {
        elapsedTime = sf::Time::Zero;
        showCursor = !showCursor;
    }

    // Update cursor position based on text bounds
    sf::FloatRect textBounds = textObj.getLocalBounds();
    cursor.setPosition(textObj.getPosition() + sf::Vector2f(textBounds.left + textBounds.width, textBounds.top));
}

void Textfield::draw(sf::RenderWindow& window) const
{
    window.draw(background);
    window.draw(textObj);
    if (active && showCursor) {
        window.draw(cursor);
    }
}

void Textfield::setText(const std::string& newText)
{
    text = newText;
    textObj.setString(text);
}

std::string Textfield::getText() const
{
    return text;
}

void Textfield::setPosition(const sf::Vector2f& newLocation)
{
    location = newLocation;
    textObj.setPosition(location);
}

sf::Vector2f Textfield::getPosition() const
{
    return location;
}