#ifndef GAME_GLOBALFUNCTIONS_H
#define GAME_GLOBALFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "../map/Hexagon.h"


float length(sf::Vector2f v);
float dist(sf::Vector2f v1, sf::Vector2f v2);
float rec(float x);
float randBetweenTwo(float a, float b);
sf::Vector2f rotateVecAtAlpha(sf::Vector2f v, float alpha);
sf::Vector2f vec(float rad, float alpha);
float degreeToRad(float alphaInDeg);
float radToDegree(float alphaInRad);
float absf(float x);

#endif //GAME_GLOBALFUNCTIONS_H
