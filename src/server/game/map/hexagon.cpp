#include "hexagon.h"
#include "../utils/settings.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "../utils/overloads.h"
#include "../core/assets.h"
#include <iostream>


Hexagon::Hexagon(sf::Vector2f pos, int dist):
        position(pos),
        distToCenter(dist), neighbours(), isAlive(true) {
    Map::addHex(this);
    initLifeTime();
    initSprite();
    initSpritePos();
    initNeighbours();
}

void Hexagon::draw(sf::RenderWindow &window) {
    if(isAlive)
        window.draw(sprite);
}

Hexagon::~Hexagon() {
    for(int i=0; i<6; ++i)
        if(neighbours[i]) neighbours[i]->neighbours[pos::getOppositePos(i)] = nullptr;
};


void Hexagon::initSpritePos() {
    sprite.setPosition(position);
}



void Hexagon::initNeighbours() {
    for(int i=0; i<pos::count; ++i) {
        sf::Vector2f neighbourPos = position + pos::vectorsHex[i];
        Hexagon* neighbour = Map::getHexAtMapInit(neighbourPos);
        neighbours[i] = neighbour;

        if(!neighbour && distToCenter < settings::map::MAP_RADIUS)
            neighbour = new Hexagon(neighbourPos, distToCenter+1);

        if(neighbour) {
            if (neighbour->relaxDist(distToCenter+1)) neighbour->initNeighbours();
            neighbour->neighbours[pos::getOppositePos(i)] = this;
        }
    }
}



bool Hexagon::relaxDist(int dist) {
    if(dist < distToCenter) {
        distToCenter = dist;
        initSpritePos();
        initLifeTime();
        return true;
    }
    return false;
}


void Hexagon::updateDestroying(sf::Time elapsed) {
    lifeTime += elapsed;
    if(lifeTime >= timeToDie + settings::map::destroyStep + settings::map::destroyStep) isAlive = false;
    else if(lifeTime >= timeToDie + settings::map::destroyStep) textureStage = 2;
    else if(lifeTime >= timeToDie) textureStage = 1;
    updateTextureStage();
    //std::cout<<isAlive<<"\n";
}

void Hexagon::initLifeTime() {
    timeToDie = (settings::map::centerLifeTime - settings::map::lifeTimeStep*(float)(distToCenter-1)) + settings::map::lifeTimeOffset*( ((rand()%200-100)/100.f) );
}

void Hexagon::initSprite() {
    sf::Image img = Assets::getRandomHexImg();
    texture.loadFromImage(img);
    sprite.setTexture(texture);
    textureStage = 0;
    updateTextureStage();
    float scale = settings::map::HEX_RADIUS*2 / settings::map::HEX_TEXTURE_SIZE.x;
    sprite.scale(scale,scale);
    sprite.setOrigin(275./2.,275./2.);
}

void Hexagon::updateTextureStage() {
    sprite.setTextureRect(sf::IntRect(settings::map::HEX_TEXTURE_SIZE.x*textureStage, 0, settings::map::HEX_TEXTURE_SIZE.x, settings::map::HEX_TEXTURE_SIZE.y));
}

Hexagon *Hexagon::getClosestHex(sf::Vector2f& pos) {
    Hexagon* closestHex = this;

    for(auto& hex : neighbours)
        if(hex && dist(hex->getPos(), pos) < dist(closestHex->getPos(), pos)) closestHex = hex;
    return closestHex;
}


