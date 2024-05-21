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
    spriteRotationAngleSnow += elapsed.asSeconds()*settings::hero::blizzard::rotationSpeedSnow;
    spriteRotationAngleClouds += elapsed.asSeconds()*settings::hero::blizzard::rotationSpeedCloud;
    blizzardSprite.setRotation(-spriteRotationAngleSnow);
    blizzardCloudSprite.setRotation(-spriteRotationAngleClouds);
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

std::string Blizzard::getParameter(int parCode) {
    switch (parCode) {
        case 1:
            return position;
        case 2:
            return spriteRotationAngleSnow;
        case 3:
            return spriteRotationAngleClouds;
    }
}
