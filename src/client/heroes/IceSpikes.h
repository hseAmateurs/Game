#include <SFML/Graphics.hpp>
#include "list"
#include "../utils/settings.h"
#include "../core/assets.h"
#include "circleShape.h"

class IceSpikes{
public:
    static std::list<IceSpikes*> spikesList; // all alive hero spikes here
    IceSpikes(float X, float Y, float W, float H, float Scale, float Delay): position(X,Y), w(W), h(H), scale(Scale), delay(Delay),
                                                                             warningShape(sf::Vector2f (X,Y),(settings::textures::iceSpikesWidth/2+5) * Scale,sf::Color(215,215,255)){
        spikesList.insert(spikesList.end(),this);
        // w = 126 h = 126 for current texture (ice_spikes)
        lifeTime = sf::seconds(delay+1);
        // creating spikes sprite
        sf::Image spikeImage = Assets::getIceSpikesImg();
        spikeTexture.loadFromImage(spikeImage);
        spikeSprite.setTexture(spikeTexture);
        spikeSprite.setTextureRect(sf::IntRect(0, 0, w, h));
        spikeSprite.setOrigin(settings::textures::iceSpikesWidth/2, settings::textures::iceSpikesWidth/2);
        spikeSprite.setScale(scale,scale);
        spikeSprite.setPosition(position);
    }
    ~IceSpikes(){
        spikesList.erase(std::find(spikesList.begin(), spikesList.end(), this));
    }

    static void spikesUpdate(sf::Time elapsed);
    static void drawSpikes(sf::RenderWindow &window);
    void draw(sf::RenderWindow &window);
    sf::Sprite getSprite() { return spikeSprite; }
private:
    sf::Vector2f position;
    float w, h; // basic parameters: x, y - location; w, h - width and height of the texture
    float delay; //delay before damage
    float scale; //spikes scale (default 126*126)
    sf::Time lifeTime;
    bool alive {true};
    sf::Texture spikeTexture;
    sf::Sprite spikeSprite;
    CircleShape warningShape;

    void update(sf::Time elapsed);
    void animate();
};