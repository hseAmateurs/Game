#pragma once

#include <SFML/Graphics.hpp>
#include "../utils/settings.h"
#include <cmath>

class CircleShape {
public:
    CircleShape(sf::Vector2f POS, float RADIUS, sf::Color COLOR): radius(RADIUS), sh(RADIUS), va(sf::TriangleFan, 181), pos(POS) {
        if (RADIUS>200) sh.setPointCount(RADIUS/20);
        sh.setOrigin(RADIUS, RADIUS);
        sh.setPosition(pos);
        sh.setFillColor(sf::Color::Transparent);
        paint(COLOR);
        sh.setOutlineThickness(3.f);

        float step = M_PI * 2 / 178.;
        float angle = -M_PI_2;

        va[0].position = pos;

        for (int i = 1; i < 180; ++i) {
            va[i].position = {cosf(angle) * (RADIUS + 4), sinf(angle) * (RADIUS + 4)};
            va[i].position += pos;
            angle += step;
        }
        va[180].position = pos;
    }

    void draw(sf::RenderWindow& window) {
        window.draw(sh);
        window.draw(va);
    }
    void drawShape(sf::RenderWindow& window) {
        window.draw(sh);
    }

    void relocate(sf::Vector2f dest);
    void paint(sf::Color color);

private:
    sf::CircleShape sh;
    sf::VertexArray va;
    sf::Vector2f pos;
    float radius;
};