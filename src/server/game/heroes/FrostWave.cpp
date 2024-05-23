#include "FrostWave.h"
#include <iostream>
#include "../utils/settings.h"
#include <cstring>


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

void FrostWave::getParameter(int parCode, char answer[]) {
    switch (parCode) {
        case 1:{ //position
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
