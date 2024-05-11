#ifndef GAME_SETTINGS_H
#define GAME_SETTINGS_H

#include <SFML/Graphics.hpp>



namespace settings {
    namespace screen {
        const int WIDTH = 1600;
        const int HEIGHT = 900;
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

    namespace hero {
        namespace hit {
            const float speed = 600;
            const float rotationSpeed = 500;
        }

        const float speed = 300;
    }

    namespace color {
        const std::vector<sf::Color> hex = {
                sf::Color(20, 174, 0),
                sf::Color(56, 204, 20),
                sf::Color(76, 224, 40)
        };
        const sf::Color hexStep = sf::Color(10,10,10);
    }
}



#endif //GAME_SETTINGS_H
