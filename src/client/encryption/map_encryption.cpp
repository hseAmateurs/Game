#include "map_encryption.h"
#include "../map/map.h"


char* map_encryption::encryptHexs(std::list<Hexagon*>& hexs){
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

int* map_encryption::decryptHexs(char* str) {
    bytes = str;
    int* resultStates = new int[NUMBER_OF_HEXS];
    int p=0;
    for(int i=0; i<NUMBER_OF_BYTES; ++i) {
        char byte = bytes[i];
        for(int j=0; j<4; ++j)
            if(p < NUMBER_OF_HEXS)
                resultStates[p++] = ((int)byte & (3 << (6 - j*2))) >> (6 - j*2);
    }
    return resultStates;
}