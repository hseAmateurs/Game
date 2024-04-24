#include "map.h"


#include <iostream>
#include <SFML/Graphics.hpp>

#include "map.h"


Hexagon *Map::getHex(sf::Vector2f pos) const {

    Hexagon* curHex = center->getClosestHex(pos);
    while( curHex && curHex != curHex->getClosestHex(pos) ) {
        curHex = curHex->getClosestHex(pos);
    }

    return curHex;
}