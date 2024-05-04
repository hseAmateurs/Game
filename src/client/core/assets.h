#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include <iostream>
#include <SFML/Graphics.hpp>


class Assets {
public:
    Assets() {
        if(!font.loadFromFile("../../../src/client/resources/fonts/PressStart2P-Regular.ttf")) std::cout << "FONT DO NOT LOADED\n";
        if(!heroImg.loadFromFile("../../../src/client/resources/textures/blue_hero.png")) std::cout << "HERO IMG DO NOT LOADED\n";
        if(!fireballImg.loadFromFile("../../../src/client/resources/textures/fireball.png")) std::cout << "FIREBALL IMG DO NOT LOADED\n";
        if(!destPointImg.loadFromFile("../../../src/client/resources/textures/dest_point.png")) std::cout << "DEST POINT IMG DO NOT LOADED\n";
        if(!frostWaveImg.loadFromFile("../../../src/client/resources/textures/frost_wave.png")) std::cout << "DEST POINT IMG DO NOT LOADED\n";
        if(!IceSpikesImg.loadFromFile("../../../src/client/resources/textures/ice_spikes.png")) std::cout << "DEST POINT IMG DO NOT LOADED\n";
    }

    static sf::Font& getFont() { return font; }
    static sf::Image& getHeroImg() { return heroImg; }
    static sf::Image& getFireballImg() { return fireballImg; }
    static sf::Image& getDestPointImg() { return destPointImg; }
    static sf::Image& getFrostWaveImg() { return frostWaveImg; }
    static sf::Image& getIceSpikesImg() { return IceSpikesImg; }

private:
    static sf::Font font;
    static sf::Image heroImg;
    static sf::Image fireballImg;
    static sf::Image destPointImg;
    static sf::Image frostWaveImg;
    static sf::Image IceSpikesImg;
};


#endif //GAME_ASSETS_H
