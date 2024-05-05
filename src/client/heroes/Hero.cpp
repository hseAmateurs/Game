#include "Hero.h"
#include "cmath"
#include <iostream>
#include "../core/view.h"
#include "RangeHit.h"
#include "FrostWave.h"
#include "IceSpikes.h"
#include "../utils/globalFunctions.h"

void Hero::update(sf::Time elapsed, sf::Vector2i mousePos) {
    sf::Vector2f dest = sf::Vector2f (float(mousePos.x),float(mousePos.y)) * currentCameraSize + currentCameraPos + currentCameraOffset;
    generalCooldown -= elapsed;

    // update base hits
    RangeHit::hitsUpdate(elapsed);
    hitCooldown -= elapsed;

    //update skills
    updateShapes(dest);
    IceSpikes::spikesUpdate(elapsed);
    skillCooldownQ -= elapsed;
    skillCooldownW -= elapsed;
    iceSequenceCreationTimer -= elapsed;
    if (iceSequenceCreationTimer>sf::Time::Zero)
        createIceSequence(dest);
    FrostWave::wavesUpdate(elapsed);
    skillCooldownE -= elapsed;

    // update direction (except small changes)
    updateDirection();

    // animation
    setTexture(elapsed);

    // updating position
    position += direction * speed * elapsed.asSeconds();
    heroSprite.setPosition(position);
    destinationSprite.setPosition(destination);
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
    if (activeSkill == 1) {
        rangeShapeQ.drawShape(window);
        aimShapeQ.draw(window);
    }
    if (activeSkill == 2)
        aimShapeW.draw(window);
    if (activeSkill == 3)
        rangeShapeE.drawShape(window);
    window.setMouseCursorVisible(!activeSkill);
    IceSpikes::drawSpikes(window);
    FrostWave::drawWaves(window);
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
        if (flyTime < sf::seconds(0.06))
            rectLeft = 150;
        else
            rectLeft = 300;
    }
    rectTop = (int(standTime.asSeconds())%4)*150;
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

void Hero::createRangeHit(sf::Vector2f dest){
    float yh = position.y-93, xh = position.x;
    if (lookLeft) xh -= 55;
    else xh += 35;
    if (flyTime > sf::Time::Zero) yh+=48;
    if (!(dest.x == xh && dest.y == yh)) {
        dest.x -= xh; dest.y -= yh;
        new RangeHit(xh,yh,70,70,dest.x/length(dest),dest.y/length(dest));
        hitCooldown = sf::seconds(0.5);
        genCD();
    }
}

void Hero::createFrostWave(sf::Vector2f dest){
    float yh = position.y-93, xh = position.x;
    if (lookLeft) xh -= 55;
    else xh += 35;
    if (flyTime > sf::Time::Zero) yh+=48;
    if (!(dest.x == xh && dest.y == yh)) {
        dest.x -= xh; dest.y -= yh;
        new FrostWave(xh,yh,136.f,323.f,dest.x/length(dest),dest.y/length(dest));
        skillCooldownE = sf::seconds(7);
        genCD();
        activeSkill = 0;
    }
}

void Hero::createBigIceSpikes(sf::Vector2f dest){
    new IceSpikes(dest.x, dest.y, 126.f, 126.f, 1, 1);
    skillCooldownQ = sf::seconds(5);
    genCD();
    activeSkill = 0;
}

void Hero::createIceSpikes(sf::Vector2f dest){
    new IceSpikes(dest.x, dest.y, 126.f, 126.f, 0.66, 0.66);
}

void Hero::setDestination(sf::Vector2i dest) {
    destination = {float(dest.x),float(dest.y)}; // relative to our window, out of window = negative coordinates
    destination = destination * currentCameraSize + currentCameraPos + currentCameraOffset;
}

void Hero::skillActivate(char button) {
    if (iceSequenceCreationTimer >= sf::Time::Zero)
        return;
    if (button == '0')
        activeSkill = 0;
    if (button == 'Q' && skillCooldownQ <= sf::Time::Zero)
        activeSkill = 1;
    if (button == 'W' && skillCooldownW <= sf::Time::Zero)
        activeSkill = 2;
    if (button == 'E' && !FrostWave::isWaveExist() && skillCooldownE <= sf::Time::Zero)
        activeSkill = 3;
    if (button == 'E' && FrostWave::isWaveExist())
        teleportToWave();
}

void Hero::skillCast(sf::Vector2i mp) {
    if (generalCooldown > sf::Time::Zero) return;
    sf::Vector2f dest = sf::Vector2f (float(mp.x),float(mp.y)) * currentCameraSize + currentCameraPos + currentCameraOffset;
    switch (activeSkill) {
        case 0:
            if (hitCooldown <= sf::Time::Zero)
                createRangeHit(dest);
            break;
        case 1:
            if (skillCooldownQ <= sf::Time::Zero && dist(dest,position)<1000)
                createBigIceSpikes(dest);
            break;
        case 2:
            if (skillCooldownW <= sf::Time::Zero && iceSequenceCreationTimer != sf::Time::Zero)
                iceSequenceCreationTimer = sf::seconds(3);
            break;
        case 3:
            if (skillCooldownE <= sf::Time::Zero)
                createFrostWave(dest);
            break;
    }
}

void Hero::teleportToWave() {
    position = FrostWave::getFirstWavePos();
    resetDestination();
    FrostWave::killFirstWave();
}

void Hero::resetDestination() {
    destination = position;
}

void Hero::updateShapes(sf::Vector2f dest) {
    if (activeSkill == 1) {
        rangeShapeQ.relocate(position);
        if (dist(position,dest) > 1000)
            aimShapeQ.paint(sf::Color::Red);
        else
            aimShapeQ.paint(sf::Color::White);
        aimShapeQ.relocate(dest);
    }
    if (activeSkill == 2) {
        aimShapeW.relocate(dest);
    }
    if (activeSkill == 3) {
        rangeShapeE.relocate(position);
    }
}

void Hero::createIceSequence(sf::Vector2f dest) {
    resetDestination();
    if (20 - iceSequenceCreationTimer.asMilliseconds() / 250 != iceSpikesCount) {
        createIceSpikes(dest);
        iceSpikesCount++;
    }
    if (iceSequenceCreationTimer.asMilliseconds() / 250 == 0) {
        iceSequenceCreationTimer = sf::Time::Zero;
        iceSpikesCount = 0;
        genCD();
        activeSkill = 0;
        skillCooldownW = sf::seconds(5);
    }
}
