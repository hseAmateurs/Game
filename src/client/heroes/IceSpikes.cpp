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
    if (lifeTime<sf::seconds(1) && lifeTime.asMilliseconds()/172>2) {
        spikeSprite.setTextureRect(sf::IntRect ((5-lifeTime.asMilliseconds()/172) * w,0,w,h));
    }
}
