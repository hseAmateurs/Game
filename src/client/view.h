#pragma once
#include <SFML/Graphics.hpp>
#include "settings.h"


inline sf::View view;
inline float cameraSpeed = settings::view::moveSpeed;
inline float zoomSpeed = settings::view::zoomSpeed;
inline float currentCameraSize = 1;
inline sf::Vector2f currentCameraPos = {0,0};
inline sf::Vector2f currentCameraOffset = {0,0};

inline void changeView(sf::Time elapsed, int viewWidth, int viewHeight) {
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

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && currentCameraSize < 2) {
        view.zoom(1 + zoomSpeed);
        currentCameraSize *= (1 + zoomSpeed);
        currentCameraOffset.x = -(viewWidth) * (currentCameraSize - 1) / 2;
        currentCameraOffset.y = -(viewHeight) * (currentCameraSize - 1) / 2;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::H) && currentCameraSize > 0.1) {
        view.zoom(1 - zoomSpeed);
        currentCameraSize *= (1 - zoomSpeed);
        currentCameraOffset.x = -(viewWidth) * (currentCameraSize - 1) / 2;
        currentCameraOffset.y = -(viewHeight) * (currentCameraSize - 1) / 2;
    }
    //std::cout << currentCameraSize << ' ' << currentCameraPosX + currentCameraOffsetX << ' ' << currentCameraPosY + currentCameraOffsetY << '\n';
}