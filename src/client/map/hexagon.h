
#ifndef GAME_HEXAGON_H
#define GAME_HEXAGON_H

#include "positions.h"
#include "../globalFunctions.h"
//#include "map.h"
class Map;

#define HEX_VERTEX_COUNT 6


class Hexagon {
public:
    Hexagon(Map* map, sf::Vector2f pos = {settings::screen::WIDTH/2.f, settings::screen::HEIGHT/2.f},
                     int dist = 0);

    ~Hexagon() {
        for(int i=0; i<6; ++i) {
            if(neighbours[i]) neighbours[i]->neighbours[pos::getOppositePos(i)] = nullptr;
        }
    }

    void draw(sf::RenderWindow& window) {
        window.draw(hexagonVertexes);
    }

//    Hexagon* getClosestHex(sf::Vector2f pos) {
//        Hexagon* closestHex = this;
//        for(auto& child : neighbours)
//            if(child && dist(child->getPos(), pos) < dist(closestHex->getPos(), pos)) closestHex = child;
//
//        if()
//    }



    void updateDestroying(sf::Time elapsed);

    int getDist()const { return distToCenter; }

    sf::Vector2f getPos()const { return position; }

    void setPos(sf::Vector2f& newPos) { position = newPos; initVertexes(); }

    bool relaxDist(int dist);

    void initNeighbours(Map* map);


    bool isDead() const { return !isAlive; }


    static int initCounter;

private:
    void initVertexes();
    void initLifeTime();

    sf::Time lifeTime;

    bool isAlive;

    int distToCenter;
    sf::Vector2f position;
    sf::VertexArray hexagonVertexes;
    Hexagon* neighbours[pos::hexPos::count];

};


#endif //GAME_HEXAGON_H
