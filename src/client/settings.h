#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <SFML/Graphics.hpp>



namespace settings {
    namespace screen {
        const int WIDTH = 1600;
        const int HEIGHT = 900;
    }

    namespace map {
        const int HEX_RADIUS = 33;
        const int MAP_RADIUS = 5;

        const sf::Time centerLifeTime = sf::seconds(20);
        const sf::Time lifeTimeStep = sf::seconds(4);
        const sf::Time lifeTimeOffset = sf::seconds(2);
    }
}


#endif //GAME_SETTINGS_H
