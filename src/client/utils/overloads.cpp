#include "overloads.h"

sf::Color operator* (const sf::Color &color, const float k) {
    return sf::Color(color.r*k, color.g*k, color.b*k, color.a);
}
