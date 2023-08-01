#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include <memory>
#include "block.h"
#include "level.h"
#include "scoremanager.h"

using namespace std;

class BiquadrisGame;

class Board
{
    vector<vector<pair<char, shared_ptr<Block>>>> board;
    vector<shared_ptr<Block>> blocks;
    shared_ptr<Block> currBlock;
    shared_ptr<Block> nextBlock;
    BiquadrisGame *game; // not ownership
    unique_ptr<ScoreManager> scoreManager;
    // vector<Debuff> debuffs;
    // CommandManager commandManager;
    Level level;

public:
    bool turnInProgress = false;

    // Debuff flags
    bool isBlinded = false;
    bool isHeavy = false;

    Board(BiquadrisGame *game, string filename);
    Block GenerateBlock();
    pair<int, int> UpdateFilledRows();
    void Init();
    void Restart();
    void AddDebuff();
    void UpdateDebuffs();
    void UpdateScore(int, int);
    void UpdateNextBlock();
    void AddBlock(Block &);
    void SetNoRandom(bool flag, string filename = "");

    const vector<vector<pair<char, shared_ptr<Block>>>> &GetGrid() const;
    const int GetLevel() const;
    void SetLevel(int);
    const int GetScore() const;
    Block &GetCurrBlock() const;
    const Block &GetNextBlock() const;
    BiquadrisGame &GetGame() const;
};

#endif
