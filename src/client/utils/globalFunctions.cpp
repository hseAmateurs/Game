#include "globalFunctions.h"
#include "../map/Hexagon.h"

float length(sf::Vector2f v) {
    return sqrtf(powf(v.x,2) + powf(v.y,2) );
}

float dist(sf::Vector2f v1, sf::Vector2f v2) {
    return length(v2-v1);
}

float rec(float x) {
    return powf(x, -1);
}

float randBetweenTwo(float a, float b) {
    if(a>b) return randBetweenTwo(b,a);
    return a + (rand() / (float)RAND_MAX) * (b-a);
}

sf::Vector2f rotateVecAtAlpha(sf::Vector2f v, float alpha) {
    return {v.x * cosf(alpha) - v.y * sinf(alpha), v.x * sinf(alpha) + v.y * cosf(alpha)};
}

sf::Vector2f vec(float rad, float alpha) {
    return {rad * cosf(alpha), rad * sinf(alpha)};
}

float degreeToRad(float alphaInDeg) {
    return alphaInDeg / 180.f * (float)M_PI;
}

float radToDegree(float alphaInRad){
    return alphaInRad * 180.f / (float)M_PI;
}

float absf(float x) {
    if(x<0) return -x;
    return x;
}


