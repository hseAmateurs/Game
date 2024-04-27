//
// Created by vivan on 4/22/2024.
//

#ifndef GAME_POSITIONS_H
#define GAME_POSITIONS_H



#include <iostream>
#include <SFML/Graphics.hpp>
#include "../settings.h"
#include <cmath>



namespace pos {
    const float r = settings::map::HEX_RADIUS;
    const float h = r * sinf(M_PI/3.f);

    enum hexPos{
        rightTop,
        top,
        leftTop,
        leftBottom,
        bottom,
        rightBottom,
        count
    };

    int getOppositePos(int pos);

    const sf::Vector2f vectorsHex[count] = {
            //{r + h/2.f, -h},
            {r*1.5f, -h},
            {0.f, -h*2.f},
            {-r*1.5f, -h},
            {-r*1.5f, h},
            {0.f, h+h},
            {r*1.5f, h},
    };

}


#endif //GAME_POSITIONS_H
