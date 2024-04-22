#include <SFML/Graphics.hpp>
#include <cmath>

#ifndef GAME_GLOBALFUNCTIONS_H
#define GAME_GLOBALFUNCTIONS_H



float len(sf::Vector2f vector) {
    return sqrtf(vector.x * vector.x + vector.y * vector.y);
}

float dist(sf::Vector2f& v1, sf::Vector2f& v2) {
    return len(v1-v2);
}



#endif //GAME_GLOBALFUNCTIONS_H
