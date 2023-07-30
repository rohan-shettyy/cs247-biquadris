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
    Board &board;

public:
    Level(string filename, Board& board);
    Block chooseBlock();
    const int GetDifficulty() const;
    void SetLevel(int);
    void SetNoRandomFlag(bool flag);
};

#endif
