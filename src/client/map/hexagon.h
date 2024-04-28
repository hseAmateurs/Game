
#ifndef GAME_HEXAGON_H
#define GAME_HEXAGON_H

#include "positions.h"
#include "../utils/globalFunctions.h"
class Map;

#define HEX_VERTEX_COUNT 6


class Hexagon {
public:

    Hexagon(Map* map, sf::Vector2f pos = {settings::screen::WIDTH/2.f, settings::screen::HEIGHT/2.f},
                     int dist = 0);
    ~Hexagon();

    void draw(sf::RenderWindow& window);
    void updateDestroying(sf::Time elapsed);
    sf::Vector2f getPos()const { return position; }
    bool isDead() const { return !isAlive; }
private:

    void initVertexes();
    void initLifeTime();
    bool relaxDist(int dist);
    void initNeighbours(Map* map);

    Hexagon* neighbours[pos::hexPos::count];
    int distToCenter;
    sf::Vector2f position;
    sf::VertexArray hexagonVertexes;
    sf::VertexArray borderVertexes;

    sf::Time lifeTime;
    bool isAlive;
};


#endif //GAME_HEXAGON_H
