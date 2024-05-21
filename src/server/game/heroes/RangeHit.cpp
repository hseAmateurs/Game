#include "RangeHit.h"
#include <iostream>
#include "../utils/settings.h"

std::list<RangeHit*> RangeHit::hitsList;

void RangeHit::hitsUpdate(sf::Time elapsed) {
    for (RangeHit* hit:hitsList) {
        if (hit->alive)
            hit->update(elapsed);
        else {
            delete hit;
            hitsUpdate(elapsed);
            return;
        }
    }
}

void RangeHit::update(sf::Time elapsed) {
    lifeTime -= elapsed;
    if (lifeTime < sf::Time::Zero)
        alive = false;

    position += direction * speed * elapsed.asSeconds();
    spriteRotationAngle+=elapsed.asSeconds()*settings::hero::hit::rotationSpeed;
    hitSprite.setRotation(-spriteRotationAngle);
    hitSprite.setPosition(position);
}

void RangeHit::drawHits(sf::RenderWindow &window) {
    for (RangeHit* hit:hitsList) {
        window.draw(hit->getSprite());
    }
}

std::string RangeHit::getParameter(int parCode) {
    switch (parCode) {
        case 1:
            return position;
        case 2:
            return spriteRotationAngle;
    }
}
