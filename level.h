#ifndef LEVEL_H
#define LEVEL_H

#include <vector>
#include <fstream>
#include "block.h"

using namespace std;

class Level
{
    int difficulty;

    bool noRandom = false; // norandom command controls this in level 3 and 4
    ifstream sequence;
    ifstream norandomin;
    Board &board;

public:
    int turnsWithoutClearing = 0; // TODO: Difficulty 4
    Level(string filename, Board& board);
    Block chooseBlock();
    const int GetDifficulty() const;
    void SetLevel(int);
    void SetNoRandomFlag(bool flag, string filename);
};

#endif
