#include <SFML/Graphics.hpp>
#include "list"
#include "../utils/settings.h"
#include "../core/assets.h"

class RangeHit{
public:
    static std::list<RangeHit*> hitsList; // all alive hero hits here
    RangeHit(sf::Vector2f POS, float W, float H, float dirX, float dirY): position(POS), w(W), h(H), spriteRotationAngle(0) {
        hitsList.insert(hitsList.end(),this);
        // w = 70 h = 70 for current texture (fireball)
        direction.x = dirX; direction.y = dirY; // hit direction

        // creating hit sprite
        sf::Image hitImage = Assets::getFireballImg();
        hitTexture.loadFromImage(hitImage);
        hitSprite.setTexture(hitTexture);
        hitSprite.setTextureRect(sf::IntRect(0, 0, w, h));
        hitSprite.setOrigin(w/2, h/2); // origin to center
        hitSprite.setPosition(position);
    }
    ~RangeHit(){
        hitsList.erase(std::find(hitsList.begin(), hitsList.end(), this));
    }

    char* getParameter(int parCode);
    static void hitsUpdate(sf::Time elapsed);
    static void drawHits(sf::RenderWindow &window);
    sf::Sprite getSprite() { return hitSprite; }
private:
    sf::Vector2f position;
    float w, h; // basic parameters: x, y - location; w, h - width and height of the texture
    sf::Vector2f direction; // current movement speed vector with const length = 1
    float speed = settings::hero::hit::speed;
    sf::Time lifeTime = sf::seconds(settings::hero::hit::lifeTime);
    bool alive {true};
    sf::Texture hitTexture;
    sf::Sprite hitSprite;
    float spriteRotationAngle;

    void update(sf::Time elapsed);
};