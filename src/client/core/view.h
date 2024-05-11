#pragma once
#include <SFML/Graphics.hpp>
#include "../utils/settings.h"


inline sf::View view;
inline float cameraSpeed = settings::view::moveSpeed;
inline float zoomSpeed = settings::view::zoomSpeed;
inline float currentCameraSize = 1;
inline sf::Vector2f currentCameraPos = {0,0};
inline sf::Vector2f currentCameraOffset = {0,0};
inline int viewWidth = settings::screen::WIDTH;
inline int viewHeight = settings::screen::HEIGHT;

#include <iostream>



inline void changeView(sf::Time elapsed, float wheelDir, sf::Vector2i mouseCoords) {


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::C)) {
        view.setCenter(viewWidth/2,viewHeight/2);
        view.setSize(viewWidth,viewHeight);
        currentCameraPos = {0,0};
        currentCameraOffset = {0,0};
        currentCameraSize = 1;
    }

    if ( (currentCameraSize < 2 && wheelDir == -1) || (currentCameraSize > 0.01 && wheelDir == 1) ) {
        view.zoom(1 - zoomSpeed * wheelDir);
        currentCameraSize *= (1 - zoomSpeed * wheelDir);
        currentCameraOffset.x = -(viewWidth) * (currentCameraSize - 1) / 2;
        currentCameraOffset.y = -(viewHeight) * (currentCameraSize - 1) / 2;
    }

    if (mouseCoords.x > settings::screen::WIDTH-50) {
        view.move(cameraSpeed*elapsed.asMicroseconds()*currentCameraSize, 0);
        currentCameraPos.x += cameraSpeed*elapsed.asMicroseconds()*currentCameraSize;
    }
    if (mouseCoords.y > settings::screen::HEIGHT-50) {
        view.move(0, cameraSpeed*elapsed.asMicroseconds()*currentCameraSize);
        currentCameraPos.y += cameraSpeed*elapsed.asMicroseconds()*currentCameraSize;
    }
    if (mouseCoords.x < 50) {
        view.move(-cameraSpeed*elapsed.asMicroseconds()*currentCameraSize, 0);
        currentCameraPos.x += -cameraSpeed*elapsed.asMicroseconds()*currentCameraSize;
    }
    if (mouseCoords.y < 50) {
        view.move(0, -cameraSpeed*elapsed.asMicroseconds()*currentCameraSize);
        currentCameraPos.y += -cameraSpeed*elapsed.asMicroseconds()*currentCameraSize;
    }


}