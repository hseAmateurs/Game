#include <SFML/Graphics.hpp>
#include "Base.h"
#include <string>

class Hero: public Base{
public:
    Hero(const std::string &Image, float X, float Y, float W, float H) {
        w = W; h = H; // w = 140 h = 150 for current texture (blue_hero)
        x = X; y = Y; // spawn coordinates
        destination.x = x; destination.y = y;
        direction.x = 0; direction.y = 0; // no destination

        sf::Image image;
        image.loadFromFile(Image);
        texture.loadFromImage(image);
        sprite.setTexture(texture);
        sprite.setTextureRect(sf::IntRect(0, 0, w, h));
        sprite.setOrigin(80, 140); // для удобности поставил origin к ногам примерно
        sprite.setPosition(x, y);
    }

    sf::Sprite getSprite() { return sprite; }
    void update(float time, sf::Vector2i mousePosition);

private:
    float x, y, w, h; // basic parameters: x, y - location; w, h - width and height of the texture
    sf::Vector2f direction; // current movement speed vector with const length = 1
    float speed = 0.2;
    sf::Vector2i destination; // current movement goal
    sf::Texture texture;
    sf::Sprite sprite;

    void updateDirection();
};
