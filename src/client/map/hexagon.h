
#ifndef GAME_HEXAGON_H
#define GAME_HEXAGON_H


#include "positions.h"
//#include "map.h"
class Map;

#define HEX_VERTEX_COUNT 6


class Hexagon {
public:
    Hexagon(Map* map, sf::Vector2f pos = {settings::screen::WIDTH/2.f, settings::screen::HEIGHT/2.f},
                     int dist = 0);

    void draw(sf::RenderWindow& window) {
        window.draw(hexagonVertexes);

        for(auto& neighbour : neighbours) {
            if(neighbour != nullptr) {
                window.draw(neighbour->hexagonVertexes);
            }
        }
    }

    //int getDist()const { return distToCenter; }

    sf::Vector2f getPos()const { return position; }

    void setPos(sf::Vector2f& newPos) { position = newPos; initVertexes(); }

    void link(Hexagon* linker, int linkPos);

    Hexagon* getClosestHex(sf::Vector2f& coords);

    bool relaxDist(int dist);

    void initNeighbours(Map* map);


private:
    void initVertexes();



    int distToCenter;
    sf::Vector2f position;
    sf::VertexArray hexagonVertexes;
    Hexagon* neighbours[pos::hexPos::count];
};


#endif //GAME_HEXAGON_H
