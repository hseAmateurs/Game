
#include "tree.h"
#include "map.h"
#include "hexagon.h"

Tree::Tree(sf::Vector2f posRelToCenter): pos(posRelToCenter + settings::screen::CENTER), isAlive(true), HP(5) {
    ground = Map::getHex(pos);
    Map::addTree(this);
    initSprite();

}

void Tree::update() {
    isAlive = !ground->isDead();
}

void Tree::draw(sf::RenderWindow &window) {
    if(isAlive)
        window.draw(sprite);
}

void Tree::initSprite() {
    sf::Image image = Assets::getTreeImg();
    texture.loadFromImage(image);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, settings::map::tree::imgSize.x, settings::map::tree::imgSize.y));
    sprite.setOrigin(settings::map::tree::imgSize.x/2.f, settings::map::tree::imgSize.y/2.f);
    float scale = settings::map::tree::radius / settings::map::tree::imgSize.x * 2.;
    sprite.scale(scale, scale);
    sprite.setPosition(pos);
}
