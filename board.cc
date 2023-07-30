#include <vector>
#include <memory>
#include <string>

#include "biquadrisgame.h"
#include "block.h"

#include "board.h"

// Constructor
Board::Board(shared_ptr<BiquadrisGame> game, string filename) : board{18, vector<pair<char, shared_ptr<Block>>>{11, {' ', nullptr}}},
                                                                currBlock{nullptr},
                                                                nextBlock{nullptr},
                                                                game{game},
                                                                level{filename}
{
}

void Board::Init()
{
    currBlock = make_shared<Block>(generateBlock());
    nextBlock = make_shared<Block>(generateBlock());
}

Block Board::generateBlock()
{
    return level.chooseBlock();
}

void Board::updateFilledRows(int numRows)
{
    // Implement the logic to update the filled rows on the board
    // You can use the 'numRows' parameter to indicate how many rows were filled
}

void Board::restart()
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

void Board::addDebuff()
{
    // Implement the logic to add a debuff to the board
    // Update the 'debuffs' vector or perform other necessary actions
}

void Board::updateDebuffs()
{
    // Implement the logic to update the debuffs on the board
    // Update the 'debuffs' vector or perform other necessary actions
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
    nextBlock = make_shared<Block>(generateBlock());
}

// assuming we can add the block to the board and there is no overlap
void Board::AddBlock(shared_ptr<Block> blockPtr)
{
    vector<pair<int, int>> coords = blockPtr->getCoords();
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
    {
        int row = coords[i].first;
        int col = coords[i].second;
        shared_ptr<Block> copiedPtr = blockPtr;
        board[row][col] = {blockPtr->GetType(), copiedPtr};
    }
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
    return scoreManager.GetScore();
}

Block& Board::GetCurrBlock() const
{
    return *currBlock;
}

const Block& Board::GetNextBlock() const
{
    return *nextBlock;
}
