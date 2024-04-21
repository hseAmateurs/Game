#include "Hero.h"
#include "cmath"
#include <iostream>
#include "view.h"
#include "RangeHit.h"

void Hero::update(float time, sf::Vector2i mousePosition) {
    // catch right_button mouse click and set destination
    if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
        destination = {float(mousePosition.x),float(mousePosition.y)}; // relative to our window, out of window = negative coordinates
        destination.x = destination.x * currentCameraSize + currentCameraPosX + currentCameraOffsetX;
        destination.y = destination.y * currentCameraSize + currentCameraPosY + currentCameraOffsetY;
    }

    // catch left_button mouse click and create/update base hits
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && hitColdown <= 0)
        createRangeHit(mousePosition);
    RangeHit::hitsUpdate(time);
    hitColdown-=time;


    // update direction (except small changes)
    updateDirection();

    // animation
    setTexpure(time);

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
    RangeHit::drawHits(window);
    window.draw(destinationSprite);
    window.draw(heroSprite);
}

void Hero::setTexpure(float time) {
    int rectLeft = 0, rectTop = 0;
    if (direction.x == 0 && direction.y == 0) {
        standTime += time;
        flyTime = 0;
        rectLeft = 0;
    }
    else {
        standTime = 0;
        flyTime += time;
        if (flyTime < 50)
            rectLeft = 150;
        else
            rectLeft = 300;
    }
    rectTop = (int(standTime/800)%4)*150;
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
    float destx = mp.x * currentCameraSize + currentCameraPosX + currentCameraOffsetX;
    float desty = mp.y * currentCameraSize + currentCameraPosY + currentCameraOffsetY;
    float yh = y-93, xh = x;
    if (lookLeft) xh -= 55;
    else xh += 35;
    if (flyTime>0) yh+=48;
    if (!(destx == xh && desty == yh)) {
        destx -= xh; desty -= yh;
        float len = sqrt(destx * destx + desty * desty);
        new RangeHit("../../../src/textures/fireball.png",xh,yh,70,70,destx/len,desty/len);
        hitColdown = 300; // otsosi u traktorista
    }
}
