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

    x += direction.x * speed * elapsed.asSeconds();
    y += direction.y * speed * elapsed.asSeconds();
    hitSprite.rotate(elapsed.asSeconds()*settings::hero::hit::rotationSpeed);
    hitSprite.setPosition(x,y);
}

void RangeHit::drawHits(sf::RenderWindow &window) {
    for (RangeHit* hit:hitsList) {
        window.draw(hit->getSprite());
    }
}
