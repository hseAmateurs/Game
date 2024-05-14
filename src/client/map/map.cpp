#include "map.h"
#include <SFML/Graphics.hpp>
#include "positions.h"
#include "../utils/overloads.h"
#include "../encryption/map_encryption.h"


std::list<Hexagon*> Map::hexs;
std::list<Tree*> Map::trees;
Hexagon* Map::center;

bool compHex(Hexagon* a, Hexagon* b) {
    return a->getPos().y < b->getPos().y;
}

Hexagon *Map::getHexAtMapInit(sf::Vector2f pos) {
    for(auto hex : hexs)
        if(dist(hex->getPos(), pos) < pos::h) return hex;
    return nullptr;
}

void Map::updateDestroying(sf::Time elapsed) {
    for(auto& hex : hexs)
        hex->updateDestroying(elapsed);
    for(auto& tree : trees)
        tree->update();

}

void Map::draw(sf::RenderWindow &window) {
    for(auto& hex : hexs)
        hex->draw(window);
    for(auto& tree : trees)
        tree->draw(window);
}

Hexagon *Map::getHex(sf::Vector2f pos) {
    Hexagon* curHex = center;

    while(curHex != curHex->getClosestHex(pos)) curHex = curHex->getClosestHex(pos);

    if(dist(curHex->getPos(), pos) <= settings::map::HEX_RADIUS) return curHex;

    return nullptr;
}

void Map::initTrees() {
    float alpha = degreeToRad(settings::map::tree::noTreesAlpha/2.f);
    const float delta = degreeToRad(settings::map::tree::treesAlpha);
    const float step = degreeToRad(settings::map::tree::noTreesAlpha + settings::map::tree::treesAlpha);

    const float innerRad = settings::map::tree::innerTreesRadiusInHex * settings::map::HEX_RADIUS;
    const float outerRad = settings::map::tree::outerTreesRadiusInHex * settings::map::HEX_RADIUS;

    for(int i=0; i<4; ++i) {
        initInnerTrees(vec(innerRad, randBetweenTwo(alpha, alpha+delta)));

        float outerAlphaCenter = alpha + delta/2.f;
        initOuterTrees(vec(outerRad, outerAlphaCenter + randBetweenTwo(0, delta/2.f)));
        initOuterTrees(vec(outerRad, outerAlphaCenter - randBetweenTwo(0, delta/2.f)));

        alpha += step;
    }
}

void Map::initOuterTrees(sf::Vector2f pos) {
    new Tree( rotateVecAtAlpha(pos, degreeToRad(settings::map::tree::avgDistAlphaOuter + settings::map::tree::distAlphaOffsetOuter))
    * randBetweenTwo(1.f - settings::map::tree::distRadiusScaleOffsetOuter, 1.f + settings::map::tree::distRadiusScaleOffsetOuter));
    new Tree(  rotateVecAtAlpha(pos,degreeToRad(-settings::map::tree::avgDistAlphaOuter - settings::map::tree::distAlphaOffsetOuter))
    * randBetweenTwo(1.f - settings::map::tree::distRadiusScaleOffsetOuter, 1.f + settings::map::tree::distRadiusScaleOffsetOuter));
}

void Map::initInnerTrees(sf::Vector2f pos) {
    new Tree( rotateVecAtAlpha(pos, degreeToRad(settings::map::tree::avgDistAlphaInner + settings::map::tree::distAlphaOffsetInner))
              * randBetweenTwo(1.f - settings::map::tree::distRadiusScaleOffsetInner, 1.f + settings::map::tree::distRadiusScaleOffsetInner));
    new Tree(  rotateVecAtAlpha(pos,degreeToRad(-settings::map::tree::avgDistAlphaInner + settings::map::tree::distAlphaOffsetInner))
              * randBetweenTwo(1.f - settings::map::tree::distRadiusScaleOffsetInner, 1.f + settings::map::tree::distRadiusScaleOffsetInner));
    new Tree(pos * randBetweenTwo(1.f - settings::map::tree::distRadiusScaleOffsetInner, 1.f + settings::map::tree::distRadiusScaleOffsetInner));
}


void Map::updateStatesHexs(char* code) {
    map_encryption m;
    int* states = m.decryptHexs(code);
    int i=0;
    for(auto hex : hexs) hex->setState(states[i++]);
}
