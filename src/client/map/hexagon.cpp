#include "hexagon.h"
#include "../settings.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "map.h"
#include "../overloads.h"

Hexagon::Hexagon(Map* map, sf::Vector2f pos, int dist):
        position(pos),
        hexagonVertexes(sf::TriangleFan, HEX_VERTEX_COUNT+2),
        borderVertexes(sf::LinesStrip, HEX_VERTEX_COUNT+1),
        distToCenter(dist), neighbours(), isAlive(true) {
    map->addHex(this);
    initLifeTime();
    initVertexes();
    initNeighbours(map);
}

void Hexagon::draw(sf::RenderWindow &window) {
    window.draw(hexagonVertexes);
    window.draw(borderVertexes);
}

Hexagon::~Hexagon() {
    for(int i=0; i<6; ++i)
        if(neighbours[i]) neighbours[i]->neighbours[pos::getOppositePos(i)] = nullptr;
};


void Hexagon::initVertexes() {
    hexagonVertexes[0].position = position;
    hexagonVertexes[0].color = sf::Color::White;
    for(int i=1; i<HEX_VERTEX_COUNT+2; ++i) {
        hexagonVertexes[i].position =
                position +
                (sf::Vector2f(cosf(M_PI/3.f* (float)i), sinf(M_PI/3.f* (float)i) ))*(float)settings::map::HEX_RADIUS;
        hexagonVertexes[i].color = settings::color::hexStep*15.f;
    }

    for(int i=0; i<HEX_VERTEX_COUNT+1; ++i) {
        borderVertexes[i].position =
                position +
                (sf::Vector2f(cosf(M_PI/3.f* (float)i), sinf(M_PI/3.f* (float)i) ))*(float)settings::map::HEX_RADIUS;
        borderVertexes[i].color = sf::Color::Black;
    }
}



void Hexagon::initNeighbours(Map* map) {
    for(int i=0; i<pos::count; ++i) {
        sf::Vector2f neighbourPos = position + pos::vectorsHex[i];
        Hexagon* neighbour = map->getHex(neighbourPos);
        neighbours[i] = neighbour;

        if(!neighbour && distToCenter < settings::map::MAP_RADIUS)
            neighbour = new Hexagon(map, neighbourPos, distToCenter+1);

        if(neighbour) {
            if (neighbour->relaxDist(distToCenter+1)) neighbour->initNeighbours(map);
            neighbour->neighbours[pos::getOppositePos(i)] = this;
        }
    }
}



bool Hexagon::relaxDist(int dist) {
    if(dist < distToCenter) {
        distToCenter = dist;
        initLifeTime();
        return true;
    }
    return false;
}


void Hexagon::updateDestroying(sf::Time elapsed) {
    lifeTime -= elapsed;
    if(lifeTime < sf::Time::Zero) {
        isAlive = false;
    }
}

void Hexagon::initLifeTime() {
    lifeTime = (settings::map::centerLifeTime - settings::map::lifeTimeStep*(float)(distToCenter-1)) + settings::map::lifeTimeOffset*( ((rand()%200-100)/100.f) );
}


