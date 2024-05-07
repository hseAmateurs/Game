#include "Hero.h"
#include "cmath"
#include <iostream>
#include "../core/view.h"
#include "RangeHit.h"
#include "FrostWave.h"
#include "IceSpikes.h"
#include "Blizzard.h"
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
    Blizzard::blizzardsUpdate(elapsed);
    skillCooldownR -= elapsed;

    // update direction (except small changes)
    updateDirection();

    // animation
    setTexture(elapsed);

    // updating position
    position += direction * speed * elapsed.asSeconds();
    heroSprite.setPosition(position);
    destinationSprite.setPosition(destination);
    staffPosition.y = position.y-88;
    staffPosition.x = position.x;
    if (lookLeft) staffPosition.x -= 55;
    else staffPosition.x += 52;
    if (flyTime > sf::Time::Zero) staffPosition.y +=48;
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
    if (activeSkill == 3) {
        rangeShapeE.drawShape(window);
        aimShapeE.draw(window);
    }
    if (activeSkill == 4) {
        rangeShapeR.drawShape(window);
        aimShapeR.draw(window);
    }
    window.setMouseCursorVisible(!activeSkill || iceSequenceStarted);
    IceSpikes::drawSpikes(window);
    FrostWave::drawWaves(window);
    RangeHit::drawHits(window);
    Blizzard::drawBlizzards(window);
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
            rectLeft = w;
        else
            rectLeft = w*2;
    }
    rectTop = (int(standTime.asSeconds())%4)*h;
    heroSprite.setTextureRect(sf::IntRect(rectLeft, rectTop, w, h));
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
    if (dest != staffPosition) {
        dest -= staffPosition;
        new RangeHit(staffPosition,settings::textures::hitWidth,settings::textures::hitHeight,dest.x/length(dest),dest.y/length(dest));
        hitCooldown = sf::seconds(settings::hero::hit::coolDown);
        genCD();
    }
}

void Hero::createFrostWave(sf::Vector2f dest){
    if (dest != staffPosition) {
        dest -= staffPosition;
        new FrostWave(staffPosition,settings::textures::frostWaveWidth,settings::textures::frostWaveHeight,dest.x/length(dest),dest.y/length(dest));
        skillCooldownE = sf::seconds(settings::hero::frostWave::coolDown);
        genCD();
        activeSkill = 0;
    }
}

void Hero::createBigIceSpikes(sf::Vector2f dest){
    new IceSpikes(dest, settings::textures::iceSpikesWidth, settings::textures::iceSpikesHeight, 1, 1);
    skillCooldownQ = sf::seconds(settings::hero::iceSpikes::coolDown);
    genCD();
    activeSkill = 0;
}

void Hero::createBlizzard(sf::Vector2f dest){
    new Blizzard(dest, settings::textures::blizzardWidth, settings::textures::blizzardHeight, settings::hero::blizzard::blizzardScale);
    skillCooldownR = sf::seconds(settings::hero::blizzard::coolDown);
    genCD();
    activeSkill = 0;
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
    if (button == 'R' && skillCooldownR <= sf::Time::Zero)
        activeSkill = 4;
}

void Hero::skillCast(sf::Vector2i mp) {
    if (generalCooldown > sf::Time::Zero || iceSequenceCreationTimer >= sf::Time::Zero) return;
    sf::Vector2f dest = sf::Vector2f (float(mp.x),float(mp.y)) * currentCameraSize + currentCameraPos + currentCameraOffset;
    switch (activeSkill) {
        case 0:
            if (hitCooldown <= sf::Time::Zero)
                createRangeHit(dest);
            break;
        case 1:
            if (skillCooldownQ <= sf::Time::Zero && dist(dest,position) < settings::hero::iceSpikes::rangeRadius)
                createBigIceSpikes(dest);
            break;
        case 2:
            if (skillCooldownW <= sf::Time::Zero)
                iceSequenceCreationTimer = sf::seconds(settings::hero::iceSequence::castDuration);
            break;
        case 3:
            if (skillCooldownE <= sf::Time::Zero)
                createFrostWave(dest);
            break;
        case 4:
            if (skillCooldownR <= sf::Time::Zero && dist(dest,position) < settings::hero::blizzard::rangeRadius)
                createBlizzard(dest);
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
        if (dist(position,dest) > settings::hero::iceSpikes::rangeRadius)
            aimShapeQ.paint(sf::Color::Red);
        else
            aimShapeQ.paint(sf::Color::White);
        aimShapeQ.relocate(dest);
    }
    if (activeSkill == 2 && !iceSequenceStarted)
        aimShapeW.relocate(dest);
    if (activeSkill == 3) {
        aimShapeE.relocate(staffPosition,dest);
        rangeShapeE.relocate(staffPosition);
    }
    if (activeSkill == 4) {
        rangeShapeR.relocate(position);
        if (dist(position,dest) > settings::hero::blizzard::rangeRadius)
            aimShapeR.paint(sf::Color::Red);
        else
            aimShapeR.paint(sf::Color::White);
        aimShapeR.relocate(dest);
    }
}

void Hero::createIceSequence(sf::Vector2f dest) {
    resetDestination();
    // create iceSpikes with predetermined in settings frequency
    if (settings::hero::iceSequence::castDuration * settings::hero::iceSequence::spikesPerSecond
    - iceSequenceCreationTimer.asMilliseconds() / (1000 / settings::hero::iceSequence::spikesPerSecond) != iceSpikesCount) {
        sf::Vector2f destSlowed = {0,0};
        if (!iceSequenceStarted)
            destSlowed = dest;
        else {
            if (length(dest-lastIceSpikes) > settings::hero::iceSequence::maxSpikesStep)
                destSlowed = lastIceSpikes + (dest-lastIceSpikes) / length(dest-lastIceSpikes) * settings::hero::iceSequence::maxSpikesStep;
            else
                destSlowed = lastIceSpikes + (dest-lastIceSpikes);
        }
        iceSequenceStarted = true;
        new IceSpikes(destSlowed, settings::textures::iceSpikesWidth, settings::textures::iceSpikesHeight, settings::hero::iceSequence::spikesScale, 0.66);
        iceSpikesCount++;
        lastIceSpikes = destSlowed;
    }
    if (iceSequenceCreationTimer.asMilliseconds() / (1000 / settings::hero::iceSequence::spikesPerSecond) == 0) {
        iceSequenceCreationTimer = sf::Time::Zero;
        iceSpikesCount = 0;
        genCD();
        activeSkill = 0;
        skillCooldownW = sf::seconds(settings::hero::iceSequence::coolDown);
        iceSequenceStarted = false;
    }
}
