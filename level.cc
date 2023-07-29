#include "level.h"
#include <cstdlib> // For rand() function
#include <string>
#include <iostream>

Level::Level(string filename) : difficulty{0}, turnsWithoutClearing{0}, sequence{filename}
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
        sequence >> tileType;
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

const int Level::GetLevel() const
{
    return difficulty;
}

void Level::setLevel(int level)
{
    difficulty = level;
}