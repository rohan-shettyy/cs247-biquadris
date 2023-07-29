#ifndef LEVEL_H
#define LEVEL_H

#include "block.h"

using namespace std;

class Level
{
    int difficulty;
    int turnsWithoutClearing;

public:
    Level();
    Block chooseBlock();
    void setLevel(int);
};

#endif
