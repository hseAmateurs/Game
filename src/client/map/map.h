
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "list"
#include "hexagon.h"
#include "../utils/globalFunctions.h"

#include <iostream>


class Map {
public:
    Map(){
        center = new Hexagon(this);
    }

    void draw(sf::RenderWindow& window);
    void updateDestroying(sf::Time elapsed);
    void addHex(Hexagon* hex) { hexs.push_back(hex); }
    Hexagon* getCenter() { return center; }
    Hexagon* getHex(sf::Vector2f pos);

private:

    Hexagon* center;
    std::list<Hexagon*> hexs;
};

#endif //GAME_MAP_H
