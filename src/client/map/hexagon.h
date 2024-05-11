
#ifndef GAME_HEXAGON_H
#define GAME_HEXAGON_H

#include "positions.h"
#include "../utils/globalFunctions.h"
class Map;

#define HEX_VERTEX_COUNT 6


class Hexagon {
public:

    Hexagon(sf::Vector2f pos = {settings::screen::WIDTH/2.f, settings::screen::HEIGHT/2.f},
                     int dist = 0);
    ~Hexagon();

    void draw(sf::RenderWindow& window);
    void updateDestroying(sf::Time elapsed);
    sf::Vector2f getPos()const { return position; }
    bool isDead() const { return !isAlive; }
    Hexagon* getClosestHex(sf::Vector2f& pos);

private:

    void initLifeTime();
    bool relaxDist(int dist);
    void initNeighbours();
    void initSpritePos();
    void updateTextureStage();
    void initSprite();


    Hexagon* neighbours[pos::hexPos::count];
    int distToCenter;
    sf::Vector2f position;

    sf::Time lifeTime;
    sf::Time timeToDie;
    bool isAlive;

    int textureStage = 0;

    sf::Texture texture;
    sf::Sprite sprite;
};


#endif //GAME_HEXAGON_H
