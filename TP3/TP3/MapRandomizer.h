#pragma once

#include <iostream>
#include <chrono>
#include <thread>

#include "WorldMap.h"

using namespace std;

class MapRandomizer {
private:
    BLOCK_TYPE _world[200][200][2];
    bool flip; // which map to use
    int nbCol;
    int nbLine;

    //void print();
    void update(unsigned int iterations);
    int getVoisins(int line, int col);
    BLOCK_TYPE getBlockType(int line, int col);
    void randomizePure(bool flip = true);
public:
    MapRandomizer(WorldMap & wm);
};
