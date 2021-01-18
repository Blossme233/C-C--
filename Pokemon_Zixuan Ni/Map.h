#ifndef MAP_H
#define MAP_H

#include <string>
using namespace std;

class Map {
   private:
    char type;
    static char map[25][16];
    static char vis_map[7][7];
   public:
    Map();
    char getType(int, int);
    void readMap(string fileName);
    void littleMap(int, int);
    void AIMove(bool);
};

#endif