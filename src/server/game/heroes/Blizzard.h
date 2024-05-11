#include <SFML/Graphics.hpp>
#include "list"
#include "../utils/settings.h"
#include "../core/assets.h"
#include "circleShape.h"

class Blizzard{
public:
    static std::list<Blizzard*> blizzardsList; // all alive hero blizzards here
    Blizzard(sf::Vector2f POS, float W, float H, float Scale): position(POS), w(W), h(H), scale(Scale),
                                                                             warningShape(POS,(settings::textures::blizzardWidth/2+5) * Scale,sf::Color(215,215,255)){
        blizzardsList.insert(blizzardsList.end(),this);
        // w = 580 h = 580 for current texture (blizzard)
        lifeTime = sf::seconds(settings::hero::blizzard::lifeTime);
        // creating blizzard sprite
        sf::Image blizzardImage = Assets::getBlizzardImg();
        blizzardTexture.loadFromImage(blizzardImage);
        blizzardSprite.setTexture(blizzardTexture);
        blizzardSprite.setTextureRect(sf::IntRect(0, 0, w, h));
        blizzardSprite.setOrigin(settings::textures::blizzardWidth/2, settings::textures::blizzardWidth/2);
        blizzardSprite.setScale(scale,scale);
        blizzardSprite.setPosition(position);
        // creating blizzard cloud sprite
        sf::Image blizzardCloudImage = Assets::getBlizzardCloudImg();
        blizzardCloudTexture.loadFromImage(blizzardCloudImage);
        blizzardCloudSprite.setTexture(blizzardCloudTexture);
        blizzardCloudSprite.setTextureRect(sf::IntRect(0, 0, w, h));
        blizzardCloudSprite.setOrigin(settings::textures::blizzardWidth/2, settings::textures::blizzardWidth/2);
        blizzardCloudSprite.setScale(scale,scale);
        blizzardCloudSprite.setPosition(position);
    }
    ~Blizzard(){
        blizzardsList.erase(std::find(blizzardsList.begin(), blizzardsList.end(), this));
    }

    static void blizzardsUpdate(sf::Time elapsed);
    static void drawBlizzards(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
    sf::Sprite getSprite() { return blizzardSprite; }
private:
    sf::Vector2f position;
    float w, h; // basic parameters: x, y - location; w, h - width and height of the texture
    float scale; //blizzard scale (default 126*126)
    sf::Time lifeTime;
    bool alive {true};
    sf::Texture blizzardTexture, blizzardCloudTexture;
    sf::Sprite blizzardSprite, blizzardCloudSprite;
    CircleShape warningShape;

    void update(sf::Time elapsed);
};