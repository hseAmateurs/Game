//
// Created by vivan on 11-May-24.
//

#ifndef GAME_MAP_ENCRYPTION_H
#define GAME_MAP_ENCRYPTION_H
#include <vector>


#define NUMBER_OF_BYTES 181
#define NUMBER_OF_HEXS 721
#include <list>

class Hexagon;

class map_encryption {
public:
    map_encryption() {
        bytes = new char[NUMBER_OF_BYTES];
    }

    char* encryptHexs(std::list<Hexagon*>& hexs);

    int* decryptHexs(char* str);

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
