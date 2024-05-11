#include "circleShape.h"

void CircleShape::relocate(sf::Vector2f dest) {
    pos = dest;
    sh.setPosition(pos);
    float step = M_PI * 2 / 178.;
    float angle = -M_PI_2;
    va[0].position = pos;
    for (int i = 1; i < 180; ++i) {
        va[i].position = {cosf(angle) * (radius + 4), sinf(angle) * (radius + 4)};
        va[i].position += pos;
        va[i].color = sf::Color(170, 170, 230, 200);
        angle += step;
    }
    va[180].position = pos;
}

void CircleShape::paint(sf::Color color) {
    sh.setOutlineColor(color);
    int darker = 30;
    va[0].color = sf::Color(color.r-darker,color.g-darker,color.b-darker,0);
    for (int i = 1; i < 180; ++i) {
        va[i].color = sf::Color(color.r-darker,color.g-darker,color.b-darker,170);
    }
    va[180].color = sf::Color(color.r-darker,color.g-darker,color.b-darker,200);
}
