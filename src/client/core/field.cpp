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
}

void Field::handleLeftClick(sf::Vector2i clickCoords) {
    //std::cout << Map::getHex({(float)clickCoords.x, (float)clickCoords.y}) << std::endl;
    hero.hit(clickCoords);
}

void Field::draw(sf::RenderWindow &window) {
    Map::draw(window);
    hero.draw(window);

#ifdef SHOW_FPS
    window.draw(fps);
#endif
}
