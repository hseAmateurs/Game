#include "globalFunctions.h"


float length(sf::Vector2f v) {
    return sqrtf(powf(v.x,2) + powf(v.y,2) );
}



float dist(sf::Vector2f v1, sf::Vector2f v2) {
    return length(v2-v1);
}
