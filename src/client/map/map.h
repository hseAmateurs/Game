
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "list"
#include "hexagon.h"
#include "tree.h"
#include "../utils/globalFunctions.h"
#include <algorithm>

#include <iostream>

bool compHex(Hexagon* a, Hexagon* b);

class Map {
public:
    Map(){
        srand(settings::seeds::map);
        center = new Hexagon();
        srand(time(nullptr));
        initTrees();
        hexs.sort(compHex);
    }

    void updateStatesHexs(char *code);
    static void draw(sf::RenderWindow& window);
    static void updateDestroying(sf::Time elapsed);
    static void addHex(Hexagon* hex) { hexs.push_back(hex); }
    static void addTree(Tree* tree) { trees.push_back(tree); }
    void initTrees();
    void initOuterTrees(sf::Vector2f pos);
    void initInnerTrees(sf::Vector2f pos);
    Hexagon* getCenter() { return center; }
    static Hexagon* getHex(sf::Vector2f pos);
    static Hexagon* getHexAtMapInit(sf::Vector2f pos);

private:

    static Hexagon* center;
    static std::list<Hexagon*> hexs;
    static std::list<Tree*> trees;

};

#endif //GAME_MAP_H
