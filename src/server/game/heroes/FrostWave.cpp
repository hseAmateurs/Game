#include "FrostWave.h"
#include <iostream>
#include "../utils/settings.h"

std::list<FrostWave*> FrostWave::wavesList;

void FrostWave::update(sf::Time elapsed) {
    lifeTime -= elapsed;
    if (lifeTime < sf::Time::Zero)
        alive = false;

    position += direction * speed * elapsed.asSeconds();
    waveSprite.setPosition(position);
}

void FrostWave::drawWaves(sf::RenderWindow &window) {
    for (FrostWave* wave:wavesList) {
        window.draw(wave->getSprite());
    }
}

void FrostWave::wavesUpdate(sf::Time elapsed) {
    for (FrostWave* wave:wavesList) {
        if (wave->alive)
            wave->update(elapsed);
        else {
            delete wave;
            wavesUpdate(elapsed);
            return;
        }
    }
}

std::string FrostWave::getParameter(int parCode) {
    switch (parCode) {
        case 1:
            return position;
        case 2:
            return spriteRotationAngle;
    }
}
