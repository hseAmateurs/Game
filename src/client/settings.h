#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <SFML/Graphics.hpp>



namespace settings {
    namespace screen {
        const int WIDTH = 1600;
        const int HEIGHT = 900;
    }

    namespace view {
        const float moveSpeed = 0.0002f;
        const float zoomSpeed = 0.01f;
    }

    namespace map {
        const int HEX_RADIUS = 80;
        const int MAP_RADIUS = 9;

        const sf::Time centerLifeTime = sf::seconds(200);
        const sf::Time lifeTimeStep = sf::seconds(10);
        const sf::Time lifeTimeOffset = sf::seconds(30);
    }

    namespace hero {
        namespace hit {
            const float speed = 300;
        }

        const float speed = 100;
    }

    namespace color {
        const sf::Color hex = sf::Color(96, 244, 59);
    }
}


#endif //GAME_SETTINGS_H
