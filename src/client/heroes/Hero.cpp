#include "Hero.h"
#include "cmath"
#include <iostream>
#include "../core/view.h"
#include "RangeHit.h"
#include "../utils/globalFunctions.h"

void Hero::update(sf::Time elapsed) {
    // catch left_button mouse click and create/update base hits

    RangeHit::hitsUpdate(elapsed);
    hitColdown -= elapsed;

    // update direction (except small changes)
    updateDirection();

    // animation
    setTexture(elapsed);

    // updating position
    position += direction * speed * elapsed.asSeconds();
    heroSprite.setPosition(position);
    destinationSprite.setPosition(destination);

    Hexagon* ground = Map::getHex(position);
    if(ground == nullptr || ground->isDead()) std::cout << "HERO DIED\n"; // TODO
}

void Hero::updateDirection() {
    //get vector from current position to destination
    if (!(position.x > destination.x - 1 && position.x < destination.x + 1
    && position.y > destination.y - 1 && position.y < destination.y + 1)) {
        direction = destination - position;
    } else {
        direction = {0,0};
    }

    //normalizing a vector
    if (length(direction) != 0) {
        direction /= length(direction);
    }
}

void Hero::draw(sf::RenderWindow &window) {
    RangeHit::drawHits(window);
    window.draw(destinationSprite);
    window.draw(heroSprite);
}


void Hero::setTexture(sf::Time elapsed) {
    int rectLeft = 0, rectTop = 0;
    if (direction.x == 0 && direction.y == 0) {
        standTime += elapsed;
        flyTime = sf::Time::Zero;
        rectLeft = 0;
    }
    else {
        standTime = sf::Time::Zero;
        flyTime += elapsed;
        if (flyTime < sf::seconds(0.07))
            rectLeft = 150;
        else
            rectLeft = 300;
    }
    rectTop = (int(standTime.asSeconds()*3)%4)*150;
    heroSprite.setTextureRect(sf::IntRect(rectLeft, rectTop, 150, 150));
    if (direction.x < 0) {
        heroSprite.setScale(-1, 1);
        lookLeft = true;
    }
    if (direction.x > 0) {
        heroSprite.setScale(1,1);
        lookLeft = false;
    }
}

void Hero::createRangeHit(sf::Vector2i mp){
    sf::Vector2f dest = sf::Vector2f (float(mp.x),float(mp.y)) * currentCameraSize + currentCameraPos + currentCameraOffset;
    float yh = position.y-93, xh = position.x;
    if (lookLeft) xh -= 55;
    else xh += 35;
    if (flyTime > sf::Time::Zero) yh+=48;
    if (!(dest.x == xh && dest.y == yh)) {
        dest.x -= xh; dest.y -= yh;
        new RangeHit(xh,yh,70,70,dest.x/length(dest),dest.y/length(dest));
        hitColdown = sf::seconds(0.4); // otsosi u traktorista
    }
}

void Hero::setDestination(sf::Vector2i dest) {
    destination = {float(dest.x),float(dest.y)}; // relative to our window, out of window = negative coordinates
    destination = destination * currentCameraSize + currentCameraPos + currentCameraOffset;
}

void Hero::hit(sf::Vector2i hitDest) {
    if (hitColdown <= sf::Time::Zero)
        createRangeHit(hitDest);
}
