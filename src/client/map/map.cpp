#include "map.h"
#include <SFML/Graphics.hpp>
#include "../globalFunctions.h"


Hexagon *Map::getHex(sf::Vector2f pos) const {
    Hexagon* closestHex = hexs[0];

    for(auto& hex : hexs) {
        if( getDist(hex->getPos(), pos) < getDist(closestHex->getPos(), pos) ) closestHex = hex;
    }

    if(getDist(closestHex->getPos(), pos) < settings::map::HEX_RADIUS) return closestHex;

    return nullptr;
}