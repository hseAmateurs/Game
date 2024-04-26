#include <SFML/Graphics.hpp>
#include "list"

class RangeHit{
public:
    static std::list<RangeHit*> hitsList; // all alive hero hits here
    RangeHit(const std::string &Image, float X, float Y, float W, float H, float dirX, float dirY) {
        hitsList.insert(hitsList.end(),this);
        w = W; h = H; // w = 70 h = 70 for current texture (fireball)
        x = X; y = Y; // spawn coordinates
        direction.x = dirX; direction.y = dirY; // hit direction

        // creating hit sprite
        sf::Image hitImage;
        hitImage.loadFromFile(Image);
        hitTexture.loadFromImage(hitImage);
        hitSprite.setTexture(hitTexture);
        hitSprite.setTextureRect(sf::IntRect(0, 0, w, h));
        hitSprite.setOrigin(25, 25);
        hitSprite.setPosition(x, y);
    }
    ~RangeHit(){
        hitsList.erase(std::find(hitsList.begin(), hitsList.end(), this));
    }

    static void hitsUpdate(float time);
    static void drawHits(sf::RenderWindow &window);
    sf::Sprite getSprite() { return hitSprite; }
private:
    float x, y, w, h; // basic parameters: x, y - location; w, h - width and height of the texture
    sf::Vector2f direction; // current movement speed vector with const length = 1
    float speed = 0.4;
    float lifeTime = 1000;
    bool alive {true};
    sf::Texture hitTexture;
    sf::Sprite hitSprite;

    void update(float time);
};