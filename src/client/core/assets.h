#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H

#include <iostream>
#include <SFML/Graphics.hpp>

#define HEX_IMG_COUNT 3

class Assets {
public:
    Assets() {
        if(!font.loadFromFile("../../../src/client/resources/fonts/PressStart2P-Regular.ttf")) std::cout << "FONT DO NOT LOADED\n";
        if(!heroImg.loadFromFile("../../../src/client/resources/textures/blue_hero.png")) std::cout << "HERO IMG DO NOT LOADED\n";
        if(!fireballImg.loadFromFile("../../../src/client/resources/textures/fireball.png")) std::cout << "FIREBALL IMG DO NOT LOADED\n";
        if(!destPointImg.loadFromFile("../../../src/client/resources/textures/dest_point.png")) std::cout << "DEST POINT IMG DO NOT LOADED\n";
        if(!frostWaveImg.loadFromFile("../../../src/client/resources/textures/frost_wave.png")) std::cout << "DEST POINT IMG DO NOT LOADED\n";
        if(!IceSpikesImg.loadFromFile("../../../src/client/resources/textures/ice_spikes.png")) std::cout << "DEST POINT IMG DO NOT LOADED\n";
        if(!BlizzardImg.loadFromFile("../../../src/client/resources/textures/blizzard_snow.png")) std::cout << "DEST POINT IMG DO NOT LOADED\n";
        if(!BlizzardCloudImg.loadFromFile("../../../src/client/resources/textures/blizzard_cloud.png")) std::cout << "DEST POINT IMG DO NOT LOADED\n";
        if(!hexImgs[0].loadFromFile("../../../src/client/resources/textures/hex_texture_1.png"))std::cout << "HEX IMG 1 DO NOT LOADED\n";
        if(!hexImgs[1].loadFromFile("../../../src/client/resources/textures/hex_texture_2.png"))std::cout << "HEX IMG 2 DO NOT LOADED\n";
        if(!hexImgs[2].loadFromFile("../../../src/client/resources/textures/hex_texture_3.png"))std::cout << "HEX IMG 3 DO NOT LOADED\n";
        if(!treeImg.loadFromFile("../../../src/client/resources/textures/tree.png"))std::cout << "TREE IMG DO NOT LOADED\n";

    }

    static sf::Font& getFont() { return font; }
    static sf::Image& getHeroImg() { return heroImg; }
    static sf::Image& getFireballImg() { return fireballImg; }
    static sf::Image& getDestPointImg() { return destPointImg; }
    static sf::Image& getRandomHexImg() {
        if(rand()%9) return hexImgs[2];
        if(rand()%3) return hexImgs[1];
        return hexImgs[0];
    }
    static sf::Image& getTreeImg() { return treeImg; }
    static sf::Image& getFrostWaveImg() { return frostWaveImg; }
    static sf::Image& getIceSpikesImg() { return IceSpikesImg; }
    static sf::Image& getBlizzardImg() { return BlizzardImg; }
    static sf::Image& getBlizzardCloudImg() { return BlizzardCloudImg; }

private:
    static sf::Font font;
    static sf::Image heroImg;
    static sf::Image fireballImg;
    static sf::Image destPointImg;
    static sf::Image hexImgs[HEX_IMG_COUNT];
    static sf::Image treeImg;
    static sf::Image frostWaveImg;
    static sf::Image IceSpikesImg;
    static sf::Image BlizzardImg;
    static sf::Image BlizzardCloudImg;
};


#endif //GAME_ASSETS_H
