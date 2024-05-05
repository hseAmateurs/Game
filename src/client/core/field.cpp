#include "field.h"
#include <cmath>

void Field::update(sf::Time elapsed, sf::Vector2i mousePos) {
    hero.update(elapsed, mousePos);
    //map.updateDestroying(elapsed);
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

void Field::handleButtonE() {
    hero.skillActivate('E');
}

void Field::handleButtonQ() {
    hero.skillActivate('Q');
}

void Field::draw(sf::RenderWindow &window) {

    map.draw(window);
    hero.draw(window);

#ifdef SHOW_FPS
    window.draw(fps);
#endif
}