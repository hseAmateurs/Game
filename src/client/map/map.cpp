#include "map.h"
#include <SFML/Graphics.hpp>
#include "positions.h"

Hexagon *Map::getHex(sf::Vector2f pos) {
    for(auto hex : hexs)
        if(dist(hex->getPos(), pos) < pos::h) return hex;
    return nullptr;
}

void Map::updateDestroying(sf::Time elapsed) {
    for(auto iter = hexs.begin(); iter != hexs.end(); ++iter) {
        Hexagon* hex = *iter;
        hex->updateDestroying(elapsed);
        if(hex->isDead()) {
            hexs.erase(iter);
            delete hex;
        }
    }
}

void Map::draw(sf::RenderWindow &window) {
    for(auto& hex : hexs)
        hex->draw(window);
}
