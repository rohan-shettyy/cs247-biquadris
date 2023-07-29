#include <vector>
#include <memory>
#include <string>
#include "board.h"
#include "block.h"

// Constructor
Board::Board(string filename) : board{18, vector<pair<char, shared_ptr<Block>>>{11, {' ', nullptr}}}, currBlock{nullptr}, nextBlock{nullptr}, level{filename}
{
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
    blocks.clear();
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
