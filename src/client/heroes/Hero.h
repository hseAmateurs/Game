#pragma once

#include <SFML/Graphics.hpp>
#include "Base.h"
#include "string"
#include "queue"
#include "../utils/settings.h"
#include "../core/assets.h"
#include "circleShape.h"

class Hero: public Base{
public:
    Hero(float X, float Y, float W, float H): position(X,Y), w(W), h(H),
    aimShapeQ({X,Y},67,sf::Color::White),
    aimShapeW({X,Y},43,sf::Color::White),
    rangeShapeQ({X,Y},1000,sf::Color::White),
    rangeShapeE({X,Y},1500,sf::Color::White){

        // w = 150 h = 150 for current texture (blue_hero)
        destination = position;
        direction = {0.f,0.f}; // no destination
        // creating hero sprite
        sf::Image heroImage = Assets::getHeroImg();
        heroTexture.loadFromImage(heroImage);
        heroSprite.setTexture(heroTexture);
        heroSprite.setTextureRect(sf::IntRect(0, 0, w, h));
        heroSprite.setOrigin(80, 140); // для удобности поставил origin к ногам примерно
        heroSprite.setPosition(position);

        // creating destination point sprite
        sf::Image destinationImage = Assets::getDestPointImg();
        destinationTexture.loadFromImage(destinationImage);
        destinationSprite.setTexture(destinationTexture);
        destinationSprite.setTextureRect(sf::IntRect (0,0,25,25));
        destinationSprite.setOrigin(12.5,12.5);
        destinationSprite.setPosition(position);
    }

    void setDestination(sf::Vector2i dest);
    void skillActivate(char button);
    void skillCast(sf::Vector2i dest);

    void draw(sf::RenderWindow &window);
    void update(sf::Time elapsed, sf::Vector2i mousePos);


private:
    sf::Vector2f position;
    float w, h; // basic parameters: x, y - location; w, h - width and height of the texture
    sf::Vector2f direction; // current movement speed vector with const length = 1
    float speed = settings::hero::speed;
    sf::Time generalCooldown = sf::Time::Zero, hitCooldown = sf::Time::Zero,
    skillCooldownE = sf::Time::Zero, skillCooldownQ = sf::Time::Zero, skillCooldownW = sf::Time::Zero,
    iceSequenceCreationTimer = sf::Time::Zero;
    sf::Time flyTime = sf::Time::Zero, standTime = sf::Time::Zero; // for animation (used in setTexture)
    bool lookLeft {false}; // is texture reflected or not
    sf::Vector2f destination; // current movement goal
    sf::Texture heroTexture, destinationTexture;
    sf::Sprite heroSprite, destinationSprite;
    int activeSkill = 0; // 0 - RangeHit, 1 - Q, 2 - W, 3 - E, 4 - R
    int iceSpikesCount = 0; // for IceSequence (W)
    bool iceSequenceStarted{false}; // for slowing IceSequence (W)
    sf::Vector2f lastIceSpikes; // for slowing IceSequence (W)
    CircleShape aimShapeQ, aimShapeW;
    CircleShape rangeShapeQ, rangeShapeE;

    void updateDirection(); // calculate direction (used in update)
    void resetDestination();
    void setTexture(sf::Time elapsed); // for animation (used in update)
    void createRangeHit(sf::Vector2f dest);
    void createFrostWave(sf::Vector2f dest);
    void createBigIceSpikes(sf::Vector2f dest);
    void createIceSpikes(sf::Vector2f dest);
    void createIceSequence(sf::Vector2f dest);
    void teleportToWave();
    void genCD() {generalCooldown = sf::seconds(0.1);}
    void updateShapes(sf::Vector2f dest);
};
