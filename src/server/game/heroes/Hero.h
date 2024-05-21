#pragma once

#include <SFML/Graphics.hpp>
#include "Base.h"
#include "string"
#include "../map/map.h"
#include "queue"
#include "../utils/settings.h"
#include "../core/assets.h"
#include "circleShape.h"
#include "rectangleShape.h"
#include "string"

enum HeroSkill {
    none,
    Q,
    W,
    E,
    R,
};


class Hero: public Base{
    static std::list<Hero*> heroList; // all heroes here
public:
    Hero(sf::Vector2f pos, float W, float H): position(pos), w(W), h(H), hp(settings::hero::startHP),
    aimShapeQ(pos,settings::textures::iceSpikesWidth/2+5,sf::Color::White),
    aimShapeW(pos,(settings::textures::iceSpikesWidth/2+5) * settings::hero::iceSequence::spikesScale,sf::Color::White),
    aimShapeE(pos,{settings::hero::frostWave::lifeTime * settings::hero::frostWave::speed, settings::textures::frostWaveWidth}),
    aimShapeR(pos,(settings::textures::blizzardWidth/2+5) * settings::hero::blizzard::blizzardScale,sf::Color::White),
    rangeShapeQ(pos,settings::hero::iceSpikes::rangeRadius,sf::Color::White),
    rangeShapeE(pos,settings::hero::frostWave::speed * settings::hero::frostWave::lifeTime,sf::Color::White),
    rangeShapeR(pos,settings::hero::blizzard::rangeRadius,sf::Color::White){

        heroList.insert(heroList.end(),this);
        // w = 150 h = 150 for current texture (blue_hero)
        destination = position;
        direction = {0.f,0.f}; // no destination
        // creating hero sprite
        sf::Image heroImage = Assets::getHeroImg();
        heroTexture.loadFromImage(heroImage);
        heroSprite.setTexture(heroTexture);
        heroSprite.setTextureRect(sf::IntRect(0, 0, w, h));
        heroSprite.setOrigin(W/2, H-10); // для удобности поставил origin к ногам примерно
        heroSprite.setPosition(position);

        // creating destination point sprite
        sf::Image destinationImage = Assets::getDestPointImg();
        destinationTexture.loadFromImage(destinationImage);
        destinationSprite.setTexture(destinationTexture);
        destinationSprite.setTextureRect(sf::IntRect (0,0,25,25));
        destinationSprite.setOrigin(settings::textures::destWidth/2,settings::textures::destHeight/2);
        destinationSprite.setPosition(position);
    }

    ~Hero(){
        heroList.erase(std::find(heroList.begin(), heroList.end(), this));
    }

    void setDestination(sf::Vector2i dest);
    void skillActivate(int SFMLKeyCode);
    void resetSkill();
    void skillCast(sf::Vector2i dest);
    void killHero();
    std::string getParameter(int parCode);
    static void controlHero(const std::string &login, const int &keyPress, const int &keyCode, const int &mousePress, const int &mouseCode, const sf::Vector2i &mousePos, const sf::Time &elapsed);

    void draw(sf::RenderWindow &window);
    void update(sf::Time elapsed, sf::Vector2i mousePos);

    std::string login;

private:
    int hp;
    sf::Vector2f position, staffPosition;
    float w, h; // basic parameters: x, y - location; w, h - width and height of the texture
    sf::Vector2f direction; // current movement speed vector with const length = 1
    float speed = settings::hero::speed;
    sf::Time generalCooldown = sf::Time::Zero, hitCooldown = sf::Time::Zero,
    skillCooldownE = sf::Time::Zero, skillCooldownQ = sf::Time::Zero, skillCooldownW = sf::Time::Zero, skillCooldownR = sf::Time::Zero,
    iceSequenceCreationTimer = sf::Time::Zero; // timer for IceSequence (W)
    sf::Time flyTime = sf::Time::Zero, standTime = sf::Time::Zero; // for animation (used in setTexture)
    bool lookLeft {false}; // is texture reflected or not
    sf::Vector2f destination; // current movement goal
    sf::Texture heroTexture, destinationTexture;
    sf::Sprite heroSprite, destinationSprite;
    int activeSkill = 0; // 0 - RangeHit, 1 - Q, 2 - W, 3 - E, 4 - R
    int iceSpikesCount = 0; // for IceSequence (W)
    bool iceSequenceStarted{false}; // for slowing IceSequence (W) and correct cursor visibility
    sf::Vector2f lastIceSpikes; // for slowing IceSequence (W)
    CircleShape aimShapeQ, aimShapeW, aimShapeR; // shapes instead of cursor while skill is active
    RectangleShape aimShapeE; // shapes instead of cursor while skill is active
    CircleShape rangeShapeQ, rangeShapeE, rangeShapeR; // shapes showing skill range while skill is active
    int rectLeft = 0, rectTop = 0; // for animation

    void updateDirection(); // calculate direction (used in update)
    void resetDestination(); // set dest to pos
    void setTexture(sf::Time elapsed); // for animation (used in update)
    void createRangeHit(sf::Vector2f dest);
    void createFrostWave(sf::Vector2f dest);
    void createBigIceSpikes(sf::Vector2f dest);
    void createIceSequence(sf::Vector2f dest);
    void createBlizzard(sf::Vector2f dest);
    void teleportToWave(); // for FrostWave (E) recall
    void genCD() {generalCooldown = sf::seconds(0.1);} // prevention from skill spamming
    void updateShapes(sf::Vector2f dest); // for correct active skills display
};
