#ifndef GAME_GLOBALFUNCTIONS_H
#define GAME_GLOBALFUNCTIONS_H

#include <SFML/Graphics.hpp>
#include <cmath>
#include "../map/hexagon.h"


float length(sf::Vector2f v);
float dist(sf::Vector2f v1, sf::Vector2f v2);
float rec(float x);
float randBetweenTwo(float a, float b);
sf::Vector2f rotateVecAtAlpha(sf::Vector2f v, float alpha);
sf::Vector2f vec(float rad, float alpha);
float degreeToRad(float alphaInDeg);
float radToDegree(float alphaInRad);
float absf(float x);
void customCopy(char *c1, const char *c2, int index);
void numTo256(int x10, char (& c256)[2]);
void vectTo256(int x, int y, char (& c256)[6]);

#endif //GAME_GLOBALFUNCTIONS_H
