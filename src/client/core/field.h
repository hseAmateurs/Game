#ifndef GAME_FIELD_H
#define GAME_FIELD_H
//#define SHOW_FPS

#include "../map/map.h"
#include "../heroes/hero.h"
#include "../utils/settings.h"

class Field {
public:
    Field() : map(),
    hero(settings::screen::CENTER, settings::textures::heroWidth, settings::textures::heroHeight)
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
    void handleButton(int keyCode);

private:
    Map map;
    sf::Text fps;
    Hero hero;
};


#endif //GAME_FIELD_H
