#include "gameLobby.h"
#include <algorithm>
#include "../../common.h"
#include <algorithm>
#include <memory>


void GameLobby::addPlayer(const std::string& username, int clientSocket) {
    playerLogins.push_back(username);
    playerSockets.push_back(clientSocket);
    // ... (Potentially store username and other player data) ...
}

bool GameLobby::hasPlayer(const std::string& username) {
    for (const auto& player : playerLogins) {
        if (player == username) {
            return true; // Player found in this lobby
        }
    }
    return false; // Player not found in this lobby
}

void GameLobby::gameLoop() {
    sf::Time elapsed = lobbyClock.restart();
    field.update(elapsed);
    //std::cout<<field.countHex()<<"\n";
}

void GameLobby::setNames() {
    field.setNames(playerLogins);
}

void GameLobby::createLobbyPackage(char *message) {
    strcpy(message, field.map.encryptHexagons());

    int index = 182;
    int len = 0;

    char heroInfo[100];
    field.hero.codeHero(heroInfo, len);
    customCopy(message, heroInfo, index);
    index+=len;


    len = 0;
    char bibaInfo[100];
    field.biba.codeHero(bibaInfo, len);
    customCopy(message, bibaInfo, index);
    index+=len;


    len = 0;
    char bobaInfo[100];
    field.boba.codeHero(bobaInfo, len);
    customCopy(message, bobaInfo, index);
    index+=len;


    len = 0;
    for (auto blizzard: Blizzard::blizzardsList) { // идет код 1 для обозначения blizzard
        message[index] = '1';
        index++;
        char *code = nullptr;
        for (int i = 1; i <=3; ++i){
            int lLen = 0;
            char answer[20];
            blizzard->getParameter(i,answer, lLen);
            customCopy(code, answer,index);
            index+=lLen;
        }
    }


    for (auto frostW: FrostWave::wavesList){ // идет код 2 для обозначения frost wave
        message[index] = '2';
        index++;
        char code[10];
        for (int i = 1; i <=2; ++i){
            int lLen = 0;
            char answer[10];
            frostW->getParameter(i,answer, lLen);
            customCopy(code, answer,index);
            index+=lLen;
        }
    }

    for (auto iceSpike: IceSpikes::spikesList){ //идет код 3 для обозначения Ice spikes
        message[index] = '3';
        index++;
        char code[10];
        for (int i = 1; i <=3; ++i){
            int lLen = 0;
            char answer[10];
            iceSpike->getParameter(i,answer, lLen);
            customCopy(code, answer,index);
            index+=lLen;
        }
    }

    for (auto rHit: RangeHit::hitsList){ //идет код 4 для обозначения range hits
        message[index] = '4';
        index++;
        char code[10];
        for (int i = 1; i <=2; ++i){
            int lLen;
            char answer [10];
            rHit->getParameter(i,answer, lLen);
            customCopy(code, answer,index);
            index+=lLen;
        }
    }



}




