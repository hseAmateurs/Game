#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/settings.h"


inline sf::View view;
inline float cameraSpeed = settings::view::moveSpeed;
inline float zoomSpeed = settings::view::zoomSpeed;
inline float currentCameraSize = 1;
inline sf::Vector2f currentCameraPos = {0,0};
inline sf::Vector2f currentCameraOffset = {0,0};
inline int viewWidth = viewWidth = settings::screen::WIDTH;
inline int viewHeight = settings::screen::HEIGHT;

#include <iostream>



inline void changeView(sf::Time elapsed, float wheelDir) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        view.move(cameraSpeed*elapsed.asMicroseconds()*currentCameraSize, 0);
        currentCameraPos.x += cameraSpeed*elapsed.asMicroseconds()*currentCameraSize;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        view.move(0, cameraSpeed*elapsed.asMicroseconds()*currentCameraSize);
        currentCameraPos.y += cameraSpeed*elapsed.asMicroseconds()*currentCameraSize;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        view.move(-cameraSpeed*elapsed.asMicroseconds()*currentCameraSize, 0);
        currentCameraPos.x += -cameraSpeed*elapsed.asMicroseconds()*currentCameraSize;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        view.move(0, -cameraSpeed*elapsed.asMicroseconds()*currentCameraSize);
        currentCameraPos.y += -cameraSpeed*elapsed.asMicroseconds()*currentCameraSize;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        view.setCenter(viewWidth/2,viewHeight/2);
        view.setSize(viewWidth,viewHeight);
        currentCameraPos = {0,0};
        currentCameraOffset = {0,0};
        currentCameraSize = 1;
    }

    if ( (currentCameraSize < 2 && wheelDir == -1) || (currentCameraSize > 0.1 && wheelDir == 1) ) {
        view.zoom(1 - zoomSpeed * wheelDir);
        currentCameraSize *= (1 - zoomSpeed * wheelDir);
        currentCameraOffset.x = -(viewWidth) * (currentCameraSize - 1) / 2;
        currentCameraOffset.y = -(viewHeight) * (currentCameraSize - 1) / 2;
    }
}
