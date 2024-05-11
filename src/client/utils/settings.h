#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <SFML/Graphics.hpp>


namespace settings {
    namespace screen {
        const int WIDTH = 1920;
        const int HEIGHT = 1080;
        const sf::Vector2f CENTER = {WIDTH/2., HEIGHT/2.};
    }

    namespace anim {
        const double f = 2.5;
        const double z = 1;
        const double r = 0;
    }

    namespace view {
        const float moveSpeed = 0.001f;
        const float zoomSpeed = 0.1f;
    }

    namespace map {
        const float HEX_RADIUS = 80;
        const int MAP_RADIUS = 15;

        const sf::Time centerLifeTime = sf::seconds(150);
        const sf::Time lifeTimeStep = sf::seconds(12);
        const sf::Time lifeTimeOffset = sf::seconds(5);
        const sf::Time destroyStep = sf::seconds(1); // 2 destroy step

        const sf::Vector2f HEX_TEXTURE_SIZE = {275,300};

        namespace tree {
            const float avgDistAlphaInner = 13;
            const float distAlphaOffsetInner = 3;
            const float distRadiusScaleOffsetInner = 0.1f;

            const float avgDistAlphaOuter = 2;
            const float distAlphaOffsetOuter = 2;
            const float distRadiusScaleOffsetOuter = 0.05f;

            const float innerTreesRadiusInHex = 7;
            const float outerTreesRadiusInHex = 15;

            const float noTreesAlpha = 35;
            const float treesAlpha = (360-noTreesAlpha*4) / 4;

            const float radius = 110;
            const sf::Vector2f imgSize = {275, 275};
        }
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
        const float blizzardWidth = 1100;
        const float blizzardHeight = 1100;
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
        namespace blizzard {
            const float rangeRadius = 1000;
            const float coolDown = 10;
            const float rotationSpeedSnow = 100;
            const float rotationSpeedCloud = 200;
            const float lifeTime = 8;
            const float blizzardScale = 1;
        }

        const float speed = 200;
    }

}



#endif //GAME_SETTINGS_H
