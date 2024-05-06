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

    namespace textures {
        const float heroWidth = 150;
        const float heroHeight = 150;
        const float destWidth = 25;
        const float destHeight = 25;
        const float hitWidth = 70;
        const float hitHeight = 70;
        const float iceSpikesWidth = 126;
        const float iceSpikesHeight = 126;
        const float frostWaveWidth = 136;
        const float frostWaveHeight = 323;
    }

    namespace hero {
        namespace hit {
            const float speed = 500;
            const float rotationSpeed = 400;
            const float lifeTime = 1.4;
            const float coolDown = 0.7;
        }
        namespace iceSpikes {
            const float rangeRadius = 1000;
            const float coolDown = 5;
        }
        namespace iceSequence {
            const float spikesScale = 0.66;
            const float castDuration = 3;
            const int spikesPerSecond = 4;
            const float maxSpikesStep = 30;
            const float coolDown = 5;
        }
        namespace frostWave {
            const float speed = 300;
            const float lifeTime = 5;
            const float coolDown = 7;
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
