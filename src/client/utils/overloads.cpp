#include "overloads.h"


std::ostream& operator<< (std::ostream& out, sf::Vector2f vec) {
    out << "{ " << vec.x << ", " << vec.y << " }";
    return out;
}
