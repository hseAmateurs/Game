#include "IceSpikes.h"
#include <iostream>
#include "../utils/settings.h"
#include "../utils/globalFunctions.h"
#include <cstring>

std::list<IceSpikes*> IceSpikes::spikesList;

void IceSpikes::spikesUpdate(sf::Time elapsed) {
    for (IceSpikes* spike:spikesList) {
        if (spike->alive)
            spike->update(elapsed);
        else {
            delete spike;
            spikesUpdate(elapsed);
            return;
        }
    }
}

void IceSpikes::update(sf::Time elapsed) {
    lifeTime -= elapsed;
    if (lifeTime < sf::Time::Zero)
        alive = false;
    animate();
}

void IceSpikes::drawSpikes(sf::RenderWindow &window) {
    for (IceSpikes* spike:spikesList) {
        spike->draw(window);
    }
}

void IceSpikes::draw(sf::RenderWindow &window) {
    if (lifeTime<sf::seconds(1))
        window.draw(spikeSprite);
    else
        warningShape.draw(window);
}

void IceSpikes::animate() {
    if (lifeTime<sf::seconds(1)) {
        textureNumber = 5-lifeTime.asMilliseconds()/172;
        if (lifeTime.asMilliseconds()/172>2)
            spikeSprite.setTextureRect(sf::IntRect (textureNumber * w,0,w,h));
    } else
        textureNumber = -1;
}

void IceSpikes::getParameter(int parCode, char answer[]) {
    switch (parCode) {
        case 1:{ //position
            char vect[6];
            vectTo256(static_cast<int>(position.x), static_cast<int>(position.x), vect); // это очень грязно, здесь все может пойти плохо
            strcpy(answer, vect);
        }
        case 2: {
            char num[1];
            num[0] = textureNumber + 1;
            strcpy(answer, num);
        } // from -1 to 3, можешь просто +1 сделать если с отрицательными там сложнее, только напиши в тг об этом
        case 3:{
            char num[1];
            num[0] = scaleVariation;
            strcpy(answer, num);
        }
    }
}
