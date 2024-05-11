#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/settings.h"
#include <cmath>

class RectangleShape {
public:
    RectangleShape(sf::Vector2f POS, sf::Vector2f SIZE): size(SIZE), sh(SIZE), pos(POS) {
        sh.setOrigin(0,size.y/2);
        sh.setPosition(pos);
        sh.setFillColor(sf::Color(255,255,255,100));
        sh.setOutlineThickness(3.f);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sh);
    }

    void relocate(sf::Vector2f heroPos, sf::Vector2f dest);

private:
    sf::RectangleShape sh;
    sf::Vector2f pos, size;
};