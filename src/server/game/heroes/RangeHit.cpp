#include "RangeHit.h"
#include <iostream>
#include <cstring>
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

void RangeHit::getParameter(int parCode, char answer[]) {
    switch (parCode) {
        case 1: { //position
            char vect[6];
            vectTo256(position.x, position.y, vect);
            strcpy(answer, vect);
        }
        case 2: {// spriteRotationAngle
            char cHp[1];
            cHp[0] = spriteRotationAngle;
            strcpy(answer, cHp);
        }
    }
}
