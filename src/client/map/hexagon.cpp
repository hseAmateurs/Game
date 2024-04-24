#include "hexagon.h"


#include <iostream>
#include <SFML/Graphics.hpp>
#include "../globalFunctions.h"

#include "hexagon.h"
#include "map.h"


Hexagon* Hexagon::getClosestHex(sf::Vector2f& coords) {
    Hexagon* closestHex = this;

    for(auto& neighbour : neighbours) {
        if(neighbour != nullptr &&
           getDist(neighbour->getPos(), coords) < getDist(closestHex->getPos(), coords) )
            closestHex = neighbour;
    }


    if(getDist(closestHex->getPos(), coords) > settings::map::HEX_RADIUS)
        return nullptr;

    return closestHex;
}

void Hexagon::initVertexes() {
    hexagonVertexes[0].position = position;
    hexagonVertexes[0].color = sf::Color(100,250,100);

    for(int i=1; i<HEX_VERTEX_COUNT+2; ++i) {
        hexagonVertexes[i].position =
                position +
                (sf::Vector2f(cosf(M_PI/3.f* (float)i), sinf(M_PI/3.f* (float)i) ))*(float)settings::map::HEX_RADIUS;
        hexagonVertexes[i].color = sf::Color(100,200,100);
    }
}

void Hexagon::initNeighbours(Map* map) {

    for(int i=0; i<pos::count; ++i) {

        sf::Vector2f neighbourPos = position + pos::vectorsHex[i];
        Hexagon* neighbour = map->getHex(neighbourPos);
        neighbours[i] = neighbour;


        if(neighbour == nullptr && distToCenter < settings::map::MAP_RADIUS) {
            neighbour = new Hexagon(map, neighbourPos, distToCenter+1);
            neighbour->initNeighbours(map);
        }

        if(neighbour != nullptr) {
            if (neighbour->relaxDist(distToCenter+1)) neighbour->initNeighbours(map);
            neighbour->link(this, i);
        }
    }
}

void Hexagon::link(Hexagon *linker, int posRelToLinker) {
    int posRelToThis = (posRelToLinker + pos::count/2) % pos::count;

    if(neighbours[posRelToThis] != nullptr) return;

    neighbours[posRelToThis] = linker;
    linker->link(this, posRelToThis);
}

bool Hexagon::relaxDist(int dist) {
    if(dist < distToCenter) {
        distToCenter = dist;
        return true;
    }
    return false;
}

Hexagon::Hexagon(Map* map, sf::Vector2f pos, int dist):
    position(pos),
    hexagonVertexes(sf::TriangleFan, HEX_VERTEX_COUNT+2),
    distToCenter(dist), neighbours() {
        initVertexes();
        map->addHex(this);
};

