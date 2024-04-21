#include "RangeHit.h"
#include <iostream>

std::list<RangeHit*> RangeHit::hitsList;

void RangeHit::hitsUpdate(float time) {
    for (RangeHit* hit:hitsList) {
        if (hit->alive)
            hit->update(time);
        else {
            delete hit;
            hitsUpdate(time);
            return;
        }
    }
}

void RangeHit::update(float time) {
    lifeTime -= time;
    if (lifeTime < 0)
        alive = false;

    x += direction.x * speed * time;
    y += direction.y * speed * time;
    hitSprite.setPosition(x,y);
}

void RangeHit::drawHits(sf::RenderWindow &window) {
    for (RangeHit* hit:hitsList) {
        window.draw(hit->getSprite());
    }
}
