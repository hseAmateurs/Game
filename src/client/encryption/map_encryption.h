//
// Created by vivan on 11-May-24.
//

#ifndef GAME_MAP_ENCRYPTION_H
#define GAME_MAP_ENCRYPTION_H
#include <vector>
#include "../map/map.h"

#define NUMBER_OF_BYTES 181
#define NUMBER_OF_HEXS 721


class map_encryption {
public:
    map_encryption() {
        bytes = new char[NUMBER_OF_BYTES];
    }
    git
    char* encryptHexs(std::list<Hexagon*>& hexs) {
        int states[4];
        for(auto& hex : hexs) {
            if(currentStatesPos >= 4) {
                encryptByte(states);
                currentStatesPos = 0;
            }
            states[currentStatesPos++] = hex->getState();
        }
        if(currentStatesPos)
            encryptByte(states);

        return bytes;
    }

    int* decryptHexs(char* str) {
        bytes = str;
        int* resultStates = new int[NUMBER_OF_HEXS];
        int p=0;
        for(int i=0; i<NUMBER_OF_BYTES; ++i) {
            char byte = bytes[i];
            for(int j=0; j<4; ++j) {
                resultStates[p++] = ((int)byte & (3 << (6 - j*2))) >> (6 - j*2);
            }
        }
        return resultStates;
    }

private:
    void encryptByte(const int states[4]) {
        char& byte = bytes[currentByte++];
        for(int i=0; i<4; ++i)
            byte |= states[i] << (6 - 2*i);
    }


    char* bytes;
    int currentStatesPos = 0;
    int currentByte = 0;
};


#endif //GAME_MAP_ENCRYPTION_H
