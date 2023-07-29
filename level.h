#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <fstream>
#include "block.h"

using namespace std;

class Level
{
    int difficulty;
    int turnsWithoutClearing;

    bool noRandom = false; // norandom command controls this in level 3 and 4
    ifstream sequence;

public:
    Level(string filename);
    Block chooseBlock();
    void setLevel(int);
    void SetNoRandomFlag(bool flag);
};

#endif
