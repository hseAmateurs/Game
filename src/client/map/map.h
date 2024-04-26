
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "hexagon.h"
#include "../globalFunctions.h"




class Map {
public:
    Map(){
        center = new Hexagon(this);
        std::cout << hexs.size();
    }

    void draw(sf::RenderWindow& window) {
        for(auto& hex : hexs)
            hex->draw(window);
    }


    void updateDestroying(sf::Time elapsed);

    void addHex(Hexagon* hex) { hexs.push_back(hex); }

    Hexagon* getCenter() { return center; }

    Hexagon* getHex(sf::Vector2f pos) const;



private:

    Hexagon* center;
    std::vector<Hexagon*> hexs;
};

#endif //GAME_MAP_H
