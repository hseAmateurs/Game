
#ifndef GAME_MAP_H
#define GAME_MAP_H

#include "list"
#include "hexagon.h"
#include "tree.h"
#include "../utils/globalFunctions.h"
#include <algorithm>

#include <iostream>
#include "../encryption/map_encryption.h"


bool compHexByHeight(Hexagon* a, Hexagon* b);

class Map {
public:
    Map(){
        center = new Hexagon();
        initTrees();
        hexs.sort(compHexByHeight);
    }

    static int* decryptHexagons(char* str);
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
    static map_encryption crypt;
};

#endif //GAME_MAP_H
