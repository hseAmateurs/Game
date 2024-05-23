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

void customCopy(char *c1, const char *c2, int index){
    for (int i = 0; i < sizeof(c2); ++i){
        c1[index+i] = c2[i];
    }
}

void numTo256(int x10, char (& c256)[2]){
    if (x10 < 0)
        x10 *= -1;
    int x1, x2;
    if (x10 > 256){
        x2 = x10 % 256;
        x10 /= 256;
        x1 = x10 % 256;
    } else {
        x1 = 0;
        x2 = x10;

    }

    c256[0] = x1;
    c256[1] = x2;
}

void vectTo256(int x, int y, char (& c256)[6]){
    if (x >= 0)
        c256[0] = '+';
    else
        c256[0] = '-';

    char x256[2];
    numTo256(x, x256);
    customCopy(c256, x256, 1);

    if (y >= 0)
        c256[3] = '+';
    else
        c256[3] = '-';

    char y256[2];
    numTo256(y, y256);
    customCopy(c256, y256, 4);
}