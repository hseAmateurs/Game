#ifndef GAME_GLOBALFUNCTIONS_H
#define GAME_GLOBALFUNCTIONS_H


#include <SFML/Graphics.hpp>
//#include "../settings.h"
#include <cmath>


std::ostream& operator<<(std::ostream& out, sf::Vector2f& vec) {
    out << "{ " << vec.x << ", " << vec.y << " }";
    return out;
}



float getDist(const sf::Vector2f& pos1, const sf::Vector2f& pos2) {
    return powf( powf(pos1.x-pos2.x, 2) + powf(pos1.y - pos2.y, 2) , 0.5f);
}


#endif //GAME_GLOBALFUNCTIONS_H
