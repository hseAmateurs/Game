#pragma once
#include <SFML/Graphics.hpp>

inline sf::View view;
inline float cameraSpeed = 0.2f;
inline float currentCameraSize = 1;
inline float zoomSpeed = 0.001f;
inline sf::Vector2f currentCameraPos = {0,0};
inline sf::Vector2f currentCameraOffset = {0,0};

inline void changeView(float time, int viewWidth, int viewHeight) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        view.move(cameraSpeed*time*currentCameraSize, 0);
        currentCameraPos.x += cameraSpeed*time*currentCameraSize;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        view.move(0, cameraSpeed*time*currentCameraSize);
        currentCameraPos.y += cameraSpeed*time*currentCameraSize;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        view.move(-cameraSpeed*time*currentCameraSize, 0);
        currentCameraPos.x += -cameraSpeed*time*currentCameraSize;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        view.move(0, -cameraSpeed*time*currentCameraSize);
        currentCameraPos.y += -cameraSpeed*time*currentCameraSize;
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