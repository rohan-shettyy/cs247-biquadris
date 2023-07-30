#include <cstdlib> // For rand() function
#include <string>

#include "biquadrisgame.h"
#include "board.h"

#include "level.h"


Level::Level(string filename, Board& board) : difficulty{0}, turnsWithoutClearing{0}, sequence{filename}, board{board}
{
    // Constructor implementation
}

Block Level::chooseBlock()
{
    // Implement the logic to generate a new block here
    // I, J, L, O, S, Z, T
    char tileType;
    if (difficulty == 0) 
    {
        if (!(sequence >> tileType))
        {
            board.GetGame().SetGameInProgress(false);
            tileType = ' ';
        }
    }
    else
    {
        // implement further difficulty levels
        tileType = 'S';
    }

    Block chosenBlock{tileType, difficulty};
    // Return the generated block
    return chosenBlock;
}

const int Level::GetDifficulty() const
{
    return difficulty;
}

void Level::SetLevel(int level)
{
    difficulty = level;
}