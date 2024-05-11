#ifndef GAME_TREE_H
#define GAME_TREE_H


#include "../core/assets.h"
#include "../utils/settings.h"
#include "../utils/overloads.h"


class Map;
class Hexagon;


class Tree {
public:
    explicit Tree(sf::Vector2f pos);

    void update();

    void draw(sf::RenderWindow& window);

    void initSprite();


private:
    Hexagon* ground;
    sf::Vector2f pos;

    int HP;

    sf::Texture texture;
    sf::Sprite sprite;

    bool isAlive;
};


#endif //GAME_TREE_H
