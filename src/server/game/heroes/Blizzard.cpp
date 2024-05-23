#include "Blizzard.h"
#include <cstring>
#include <iostream>
#include "../utils/settings.h"
#include "../utils/globalFunctions.h"

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

void Blizzard::getParameter(int parCode, char answer[], int &len) {
    switch (parCode) {
        case 1:{ //position
            char vect[6];
            len = 6;
            vectTo256(position.x, position.y, vect);
            strcpy(answer, vect);
            break;
        }
        case 2: {// spriteRotationAngleSnow
            char cHp[1];
            len = 1;
            cHp[0] = spriteRotationAngleSnow;
            strcpy(answer, cHp);
            break;
        }
        case 3:{// spriteRotationAngleClowds
            char cHp[1];
            len = 1;
            cHp[0] = spriteRotationAngleClouds;
            strcpy(answer, cHp);
            break;
        }
    }
}
