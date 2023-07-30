#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "block.h"
#include "level.h"
#include "scoremanager.h"

using namespace std;

class Board
{
    vector<vector<pair<char, shared_ptr<Block>>>> board;
    vector<shared_ptr<Block>> blocks;
    shared_ptr<Block> currBlock;
    shared_ptr<Block> nextBlock;
    // BigquardisGame game;
    ScoreManager scoreManager;
    // vector<Debuff> debuffs;
    // CommandManager commandManager;
    Level level;

public:
    bool turnInProgress = false;

    Board(string filename);
    Block generateBlock();
    void updateFilledRows(int);
    void Init();
    void restart();
    void addDebuff();
    void updateDebuffs();
    void UpdateNextBlock();

    const vector<vector<pair<char, shared_ptr<Block>>>>& GetGrid() const;
    const int GetLevel() const;
    void SetLevel(int);
    const int GetScore() const;
    Block& GetCurrBlock() const;
    const Block& GetNextBlock() const;
};

#endif
