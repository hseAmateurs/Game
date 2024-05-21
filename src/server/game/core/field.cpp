#include "field.h"
#include <cmath>

void Field::update(sf::Time elapsed){//, sf::Vector2i mousePos) {
    //hero.update(elapsed, mousePos);
    Map::updateDestroying(elapsed);
#ifdef SHOW_FPS
    fps.setString(std::to_string((int)rec(elapsed.asSeconds())));
#endif
}

void Field::handleRightClick(sf::Vector2i clickCoords) {
    hero.setDestination(clickCoords);
    hero.resetSkill();
}

void Field::handleLeftClick(sf::Vector2i clickCoords) {
    hero.skillCast(clickCoords);
}


void Field::draw(sf::RenderWindow &window) {
    Map::draw(window);
    hero.draw(window);

#ifdef SHOW_FPS
    window.draw(fps);
#endif
}

void Field::handleButton(int SFMLKeyCode) {
    hero.skillActivate(SFMLKeyCode);
}

void Field::setNames(const std::vector<std::string> &logins) {
    hero.login = logins[0];
    biba.login = logins[1];
    boba.login = logins[2];
}
