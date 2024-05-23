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

void GameLobby::createLobbyPackege(char *message) {

    int index = 182;

    char *heroInfo = nullptr;
    field.hero.codeHero(heroInfo);
    customCopy(message, heroInfo, index);
    index+=sizeof(heroInfo);
    free(heroInfo);

    char *bibaInfo = nullptr;
    field.biba.codeHero(bibaInfo);
    customCopy(message, bibaInfo, index);
    index+=sizeof(bibaInfo);
    free(bibaInfo);

    char *bobaInfo = nullptr;
    field.hero.codeHero(bobaInfo);
    customCopy(message, bobaInfo, index);
    index+=sizeof(bobaInfo);
    free(bobaInfo);

    for (auto blizzard: Blizzard::blizzardsList) { // идет код 1 для обозначения blizzard
        message[index] = '1';
        index++;
        char *code = nullptr;
        for (int i = 1; i <=3; ++i){
            char *answer = nullptr;
            blizzard->getParameter(i,answer);
            customCopy(code, answer,index);
            index+=sizeof (answer);
        }
    }


    for (auto frostW: FrostWave::wavesList){ // идет код 2 для обозначения frost wave
        message[index] = '2';
        index++;
        char *code = nullptr;
        for (int i = 1; i <=2; ++i){
            char *answer = nullptr;
            frostW->getParameter(i,answer);
            customCopy(code, answer,index);
            index+=sizeof (answer);
        }
    }

    for (auto iceSpike: IceSpikes::spikesList){ //идет код 3 для обозначения Ice spikes
        message[index] = '3';
        index++;
        char *code = nullptr;
        for (int i = 1; i <=3; ++i){
            char *answer = nullptr;
            iceSpike->getParameter(i,answer);
            customCopy(code, answer,index);
            index+=sizeof (answer);
        }
    }

    for (auto rHit: RangeHit::hitsList){ //идет код 4 для обозначения range hits
        message[index] = '4';
        index++;
        char *code = nullptr;
        for (int i = 1; i <=2; ++i){
            char *answer = nullptr;
            rHit->getParameter(i,answer);
            customCopy(code, answer,index);
            index+=sizeof (answer);
        }
    }



}




