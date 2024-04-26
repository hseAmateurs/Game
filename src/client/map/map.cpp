#include "map.h"
#include <SFML/Graphics.hpp>
#include "positions.h"



Hexagon *Map::getHex(sf::Vector2f pos) {
    Hexagon* hex;
    int n = hexs.size();

    for(int i=n-1; i>=0; --i) {
        hex = hexs[i];
        if(dist(hex->getPos(), pos) < pos::h) return hex;
    }

    return nullptr;
}

void Map::updateDestroying(sf::Time elapsed) {
    for(int i=0; i<hexs.size(); ++i) {
        Hexagon* hex = hexs[i];
        hex->updateDestroying(elapsed);
        if(hex->isDead()) {
            hexs.erase(hexs.begin()+i);
            delete hex;
            --i;
        }
    }

}
