#pragma once

#include <SFML/Graphics.hpp>
#include "list"
#include "../utils/settings.h"
#include "../core/assets.h"
#include <cmath>

class FrostWave{
public:
    static std::list<FrostWave*> wavesList; // all alive hero hits here
    FrostWave(float X, float Y, float W, float H, float dirX, float dirY): position(X,Y), w(W), h(H) {
        wavesList.insert(wavesList.end(),this);
        // w = 136 h = 323 for current texture (frost_wave)
        direction.x = dirX; direction.y = dirY; // wave direction

        // creating wave sprite
        sf::Image waveImage = Assets::getFrostWaveImg();
        waveTexture.loadFromImage(waveImage);
        waveSprite.setTexture(waveTexture);
        waveSprite.setTextureRect(sf::IntRect(0, 0, w, h));
        waveSprite.setOrigin(120, 162);
        waveSprite.setPosition(position);
        if(dirY>0) waveSprite.setRotation(acosf(dirX)*180.f/M_PI);
        else waveSprite.setRotation(-acosf(dirX)*180.f/M_PI);
        waveSprite.setScale(0.7f,0.5f);
    }

    ~FrostWave(){
        wavesList.erase(std::find(wavesList.begin(), wavesList.end(), this));
    }

    static sf::Vector2f getFirstWavePos() {return wavesList.back()->position;}
    static void killFirstWave() {delete wavesList.back();}
    static bool isWaveExist() { return !wavesList.empty(); }
    sf::Sprite getSprite() { return waveSprite; }
    static void drawWaves(sf::RenderWindow &window);
    static void wavesUpdate(sf::Time elapsed);
private:
    sf::Vector2f position;
    float w, h; // basic parameters: x, y - location; w, h - width and height of the texture
    sf::Vector2f direction; // current movement speed vector with const length = 1
    float speed = settings::hero::frostWave::speed;
    sf::Time lifeTime = sf::seconds(4);
    bool alive {true};
    sf::Texture waveTexture;
    sf::Sprite waveSprite;

    void update(sf::Time elapsed);
};