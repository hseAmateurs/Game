#include "RectangleShape.h"
#include "../utils/globalFunctions.h"

void RectangleShape::relocate(sf::Vector2f heroPos, sf::Vector2f dest) {
    pos = heroPos;
    sh.setPosition(pos);
    sf::Vector2f dir = (dest - pos) / length(dest - pos);
    if(dir.y>0) sh.setRotation(acosf(dir.x)*180.f/M_PI);
    else sh.setRotation(-acosf(dir.x)*180.f/M_PI);
}