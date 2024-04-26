#include <SFML/Graphics.hpp>
#include "Base.h"
#include "string"
#include "settings.h"


class Hero: public Base{
public:
    Hero(const std::string &Image, float X, float Y, float W, float H): position(X,Y), w(W), h(H) {
        // w = 150 h = 150 for current texture (blue_hero)
        destination = position;
        direction = {0.f,0.f}; // no destination
        // creating hero sprite
        sf::Image heroImage;
        heroImage.loadFromFile(Image);
        heroTexture.loadFromImage(heroImage);
        heroSprite.setTexture(heroTexture);
        heroSprite.setTextureRect(sf::IntRect(0, 0, w, h));
        heroSprite.setOrigin(80, 140); // для удобности поставил origin к ногам примерно
        heroSprite.setPosition(position);

        // creating destination point sprite
        sf::Image destinationImage;
        destinationImage.loadFromFile("../../../src/textures/destination point.png");
        destinationTexture.loadFromImage(destinationImage);
        destinationSprite.setTexture(destinationTexture);
        destinationSprite.setTextureRect(sf::IntRect (0,0,25,25));
        destinationSprite.setOrigin(12.5,12.5);
        destinationSprite.setPosition(position);
    }

    void draw(sf::RenderWindow &window);
    void update(sf::Time elapsed, sf::Vector2i mousePosition);

private:
    sf::Vector2f position;
    float w, h; // basic parameters: x, y - location; w, h - width and height of the texture
    sf::Vector2f direction; // current movement speed vector with const length = 1
    float speed = settings::hero::speed;
    sf::Time hitColdown = sf::Time::Zero;
    sf::Time flyTime = sf::Time::Zero, standTime = sf::Time::Zero; // for animation (used in setTexture)
    bool lookLeft {false}; // is texture reflected or not
    sf::Vector2f destination; // current movement goal
    sf::Texture heroTexture, destinationTexture;
    sf::Sprite heroSprite, destinationSprite;

    void updateDirection(); // calculate direction (used in update)
    void setTexture(sf::Time elapsed); // for animation (used in update)
    void createRangeHit(sf::Vector2i mp);
};
