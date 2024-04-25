#include "map.h"
#include <SFML/Graphics.hpp>


Hexagon *Map::getHex(sf::Vector2f pos) const {
    Hexagon* closestHex = hexs[0];

    for(auto& hex : hexs) if(dist(hex->getPos(), pos) < dist(closestHex->getPos(), pos))
        closestHex = hex;

    if(dist(closestHex->getPos(), pos) < settings::map::HEX_RADIUS)
        return closestHex;
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
