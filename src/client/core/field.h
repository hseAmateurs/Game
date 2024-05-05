#ifndef GAME_FIELD_H
#define GAME_FIELD_H
//#define SHOW_FPS

#include "../map/map.h"
#include "../heroes/hero.h"

class Field {
public:
    Field() : map(),
    hero(settings::screen::WIDTH/2.f, settings::screen::HEIGHT/2.f, 150, 150)
    {
    #ifdef SHOW_FPS
        fps.setFont(Assets::getFont());
        fps.setCharacterSize(10);
        fps.setFillColor(sf::Color::Red);
    #endif
    }

    void update(sf::Time elapsed, sf::Vector2i mousePos);
    void draw(sf::RenderWindow& window);
    void handleRightClick(sf::Vector2i clickCoords);
    void handleLeftClick(sf::Vector2i clickCoords);
    void handleButtonQ();
    void handleButtonW();
    void handleButtonE();

private:
    Map map;
    sf::Text fps;
    Hero hero;
};


#endif //GAME_FIELD_H
