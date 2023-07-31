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
            sequence.clear();
            sequence.seekg(0);
            sequence >> tileType;
        }
    }
    else if (difficulty == 1)
    {
        int random = rand() % 12;
        if (random == 0)
        {
            tileType = 'S';
        }
        else if (random == 1)
        {
            tileType = 'Z';
        }
        else if (random == 2 || random == 3)
        {
            tileType = 'I';
        }
        else if (random == 4 || random == 5)
        {
            tileType = 'J';
        }
        else if (random == 6 || random == 7)
        {
            tileType = 'L';
        }
        else if (random == 8 || random == 9)
        {
            tileType = 'O';
        }
        else
        {
            tileType = 'T';
        }
    }
    else if (difficulty == 2)
    {
        int random = rand() % 7;
        if (random == 0)
        {
            tileType = 'S';
        }
        else if (random == 1)
        {
            tileType = 'Z';
        }
        else if (random == 2)
        {
            tileType = 'I';
        }
        else if (random == 3)
        {
            tileType = 'J';
        }
        else if (random == 4)
        {
            tileType = 'L';
        }
        else if (random == 5)
        {
            tileType = 'O';
        }
        else
        {
            tileType = 'T';
        }
    }
    else if (difficulty == 3)
    {
        int random = rand() % 9;
        if (random == 0 || random == 1)
        {
            tileType = 'S';
        }
        else if (random == 2 || random == 3)
        {
            tileType = 'Z';
        }
        else if (random == 4)
        {
            tileType = 'I';
        }
        else if (random == 5)
        {
            tileType = 'J';
        }
        else if (random == 6)
        {
            tileType = 'L';
        }
        else if (random == 7)
        {
            tileType = 'O';
        }
        else
        {
            tileType = 'T';
        }
    }
    else
    {
        // implement further difficulty levels
        tileType = 'S';
    }

    Block chosenBlock{tileType, difficulty};
    if (difficulty >= 3)
    {
        chosenBlock.isHeavy = true;
    }
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

void Level::SetNoRandomFlag(bool flag, string filename)
{
    noRandom = flag;
    norandomin.close();
    if (noRandom)
    {
        norandomin.open(filename);
    }
}