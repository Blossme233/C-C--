#include <cstdio>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#include "Map.h"

Map::Map() {
    this->type = ' ';
    for (int i = 0; i < 25; i++) {
        for (int j = 0; j < 16; j++) {
            this->map[i][j] = ' ';
        }
    }
}

char Map::getType(int x, int y) {
    //   this part of code is to get the type of that land
    return this->map[x][y];
}

void Map::littleMap(int, int) {
    //   this part of code is to get the little map that player can see
}

void Map::AIMove(bool) {
    //   this part of code is to let the wile Pokemon move
}