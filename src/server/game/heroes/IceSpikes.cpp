#include "IceSpikes.h"
#include <iostream>
#include "../utils/settings.h"

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

std::string IceSpikes::getParameter(int parCode) {
    switch (parCode) {
        case 1:
            return position;
        case 2:
            return textureNumber; // from -1 to 3, можешь просто +1 сделать если с отрицательными там сложнее, только напиши в тг об этом
        case 3:
            return scaleVariation;
    }
}
