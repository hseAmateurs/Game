#include "field.h"
#include <cmath>

void Field::update(sf::Time elapsed) {
    hero.update(elapsed);
    Map::updateDestroying(elapsed);
#ifdef SHOW_FPS
    fps.setString(std::to_string((int)rec(elapsed.asSeconds())));
#endif
}

void Field::handleRightClick(sf::Vector2i clickCoords) {
    hero.setDestination(clickCoords);
    hero.skillActivate('0');
}

void Field::handleLeftClick(sf::Vector2i clickCoords) {
    hero.skillCast(clickCoords);
}

void Field::handleButtonQ() {
    hero.skillActivate('Q');
}

void Field::handleButtonW() {
    hero.skillActivate('W');
}

void Field::handleButtonE() {
    hero.skillActivate('E');
}

void Field::handleButtonR() {
    hero.skillActivate('R');
}


void Field::draw(sf::RenderWindow &window) {
    Map::draw(window);
    hero.draw(window);

#ifdef SHOW_FPS
    window.draw(fps);
#endif
}
