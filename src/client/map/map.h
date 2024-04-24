
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "hexagon.h"




class Map {
public:
    Map(){
        center = new Hexagon(this);
        center->initNeighbours(this);
    }

    void draw(sf::RenderWindow& window) {
        for(auto& hex : hexs) {
            hex->draw(window);
        }
    }

    void addHex(Hexagon* hex) { hexs.push_back(hex); }

    Hexagon* getCenter() {return center;}

    Hexagon* getHex(sf::Vector2f pos) const;



private:

    Hexagon* center;
    std::vector<Hexagon*> hexs;
};

#endif //GAME_MAP_H
