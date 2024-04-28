#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <SFML/Graphics.hpp>



namespace settings {
    namespace screen {
        const int WIDTH = 1600;
        const int HEIGHT = 900;
    }

    namespace view {
        const float moveSpeed = 0.001f;
        const float zoomSpeed = 0.1f;
    }

    namespace map {
        const int HEX_RADIUS = 80;
        const int MAP_RADIUS = 15;

        const sf::Time centerLifeTime = sf::seconds(100);
        const sf::Time lifeTimeStep = sf::seconds(6);
        const sf::Time lifeTimeOffset = sf::seconds(10);
    }

    namespace hero {
        namespace hit {
            const float speed = 300;
            const float rotationSpeed = 400;
        }

        const float speed = 200;
    }

    namespace color {
        const std::vector<sf::Color> hex = {
                sf::Color(36, 184, 0),
                sf::Color(56, 204, 20),
                sf::Color(76, 224, 40)
        };
        const sf::Color hexStep = sf::Color(10,10,10);
    }
}



#endif //GAME_SETTINGS_H
