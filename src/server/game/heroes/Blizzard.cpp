#include "Blizzard.h"
#include <iostream>
#include "../utils/settings.h"

std::list<Blizzard*> Blizzard::blizzardsList;

void Blizzard::blizzardsUpdate(sf::Time elapsed) {
    for (Blizzard* blizzard:blizzardsList) {
        if (blizzard->alive)
            blizzard->update(elapsed);
        else {
            delete blizzard;
            blizzardsUpdate(elapsed);
            return;
        }
    }
}

void Blizzard::update(sf::Time elapsed) {
    lifeTime -= elapsed;
    if (lifeTime < sf::Time::Zero)
        alive = false;
    blizzardSprite.rotate(-elapsed.asSeconds()*settings::hero::blizzard::rotationSpeedSnow);
    blizzardCloudSprite.rotate(-elapsed.asSeconds()*settings::hero::blizzard::rotationSpeedCloud);
}

void Blizzard::drawBlizzards(sf::RenderWindow &window) {
    for (Blizzard* blizzard:blizzardsList) {
        blizzard->draw(window);
    }
}

void Blizzard::draw(sf::RenderWindow &window) {
    window.draw(blizzardSprite);
    window.draw(blizzardCloudSprite);
}
