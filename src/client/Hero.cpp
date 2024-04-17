#include "Hero.h"
#include "cmath"
#include <iostream>
#include "view.h"

void Hero::update(float time, sf::Vector2i mousePosition) {
    // catch right_button mouse click and set destination
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        destination = mousePosition; // relative to our window, out of window = negative coordinates
        destination.x = destination.x * currentCameraSize + currentCameraPosX + currentCameraOffsetX;
        destination.y = destination.y * currentCameraSize + currentCameraPosY + currentCameraOffsetY;
    }

    // update direction (except small changes)
    updateDirection();

    // updating position
    x += direction.x * speed * time;
    y += direction.y * speed * time;
    heroSprite.setPosition(x,y);
    destinationSprite.setPosition(destination.x, destination.y);
}

void Hero::updateDirection() {
    //get vector from current position to destination
    if (!(x > destination.x - 1 && x < destination.x + 1
    && y > destination.y - 1 && y < destination.y + 1)) {
        direction.x = destination.x - x;
        direction.y = destination.y - y;
    } else {
        direction.x = 0;
        direction.y = 0;
    }
    //calculate vector length
    float dirVectorLength = sqrt(direction.x * direction.x + direction.y * direction.y);

    //normalizing a vector
    if (dirVectorLength != 0) {
        direction.x /= dirVectorLength;
        direction.y /= dirVectorLength;
    }
}

void Hero::drawHero(sf::RenderWindow &window) {
    window.draw(destinationSprite);
    window.draw(heroSprite);
}
