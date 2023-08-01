#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "biquadrisgame.h"
#include "block.h"

#include "board.h"

using namespace std;

// Constructor
Board::Board(BiquadrisGame *game, string filename) : board{18, vector<pair<char, shared_ptr<Block>>>{11, {' ', nullptr}}},
                                                     currBlock{nullptr},
                                                     nextBlock{nullptr},
                                                     game{game},
                                                     scoreManager{make_unique<ScoreManager>()},
                                                     level{filename, *this}
{
}

void Board::Init()
{
    currBlock = make_shared<Block>(GenerateBlock());
    nextBlock = make_shared<Block>(GenerateBlock());
}

Block Board::GenerateBlock()
{
    return level.chooseBlock();
}

pair<int, int> Board::UpdateFilledRows()
{
    int count = 0;
    int bonus = 0;
    // Implement the logic to update the filled rows on the board
    // returns number of rows filled
    for (int row = 3; row < 18; row++)
    {
        bool fullRow = true;
        for (int col = 0; col < 11; col++)
        {
            if (board[row][col].second == nullptr)
            {
                fullRow = false;
            }
        }
        if (fullRow)
        {
            count++;
            for (int col = 0; col < 11; col++)
            {
                board[row][col].second->deleteCoord(row, col);
                board[row][col] = {' ', nullptr};
            }
            // iterate up from the row to move all the blocks
            for (int i = row - 1; i >= 3; i--)
            {
                for (int j = 0; j < 11; j++)
                {
                    if (board[i][j].second != nullptr)
                    {
                        board[i + 1][j] = board[i][j];
                        board[i + 1][j].second->shiftDownCoord(i, j);
                        board[i][j] = {' ', nullptr};
                    }
                }
            }
        }
    }
    // get and clear all the blocks that were cleared from the rows
    for (auto it = blocks.begin(); it != blocks.end();)
    {
        if ((*it).use_count() == 1) // only the blocks vector contains a pointer to the block
        {
            bonus += (*it)->GetLevel();
            it = blocks.erase(it);
        }
        else
        {
            it++;
        }
    }
    return {count, bonus};
}

void Board::Restart()
{
    // Implement the logic to restart the game
    // Reset the board and other necessary data members
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            board[i][j] = {' ', nullptr};
        }
    }
    currBlock = nullptr;
    nextBlock = nullptr;
}

void Board::AddDebuff()
{
    // Implement the logic to add a debuff to the board
    // Update the 'debuffs' vector or perform other necessary actions
}

void Board::UpdateDebuffs()
{
    // Implement the logic to update the debuffs on the board
    // Update the 'debuffs' vector or perform other necessary actions
}

void Board::UpdateScore(int rows, int blocksCleared)
{
    scoreManager->update(GetLevel(), rows, blocksCleared);
}

void Board::UpdateNextBlock()
{
    currBlock = nextBlock;
    for (auto coord : currBlock->getCoords())
    {
        if (board[coord.first][coord.second].first != ' ')
        {
            // game over
            game->Terminate(*this);
            return;
        }
    }
    nextBlock = make_shared<Block>(GenerateBlock());
}

// assuming we can add the block to the board and there is no overlap
void Board::AddBlock(Block &block)
{
    vector<pair<int, int>> coords = block.getCoords();
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
    {
        int row = coords[i].first;
        int col = coords[i].second;
        shared_ptr<Block> copiedPtr = make_shared<Block>(block);
        board[row][col] = pair<char, shared_ptr<Block>>(block.GetType(), copiedPtr);
    }
    blocks.push_back(make_shared<Block>(block));
}

void Board::SetNoRandom(bool flag, string filename)
{
    level.SetNoRandomFlag(flag, filename);
}

const vector<vector<pair<char, shared_ptr<Block>>>> &Board::GetGrid() const
{
    return board;
}

const int Board::GetLevel() const
{
    return level.GetDifficulty();
}

void Board::SetLevel(int l)
{
    level.SetLevel(l);
}

const int Board::GetScore() const
{
    return scoreManager->GetScore();
}

Block &Board::GetCurrBlock() const
{
    return *currBlock;
}

const Block &Board::GetNextBlock() const
{
    return *nextBlock;
}

BiquadrisGame &Board::GetGame() const
{
    return *game;
}
