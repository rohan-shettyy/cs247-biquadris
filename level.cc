#include "level.h"
#include <cstdlib> // For rand() function

Level::Level() : difficulty(1), turnsWithoutClearing(0)
{
    // Constructor implementation
}

Block Level::chooseBlock()
{
    // Implement the logic to generate a new block here
    // I, J, L, O, S, Z, T
    char tileType = 'S';

    Block chosenBlock{tileType, difficulty};
    // Return the generated block
    return chosenBlock;
}

void Level::setLevel(int level)
{
    difficulty = level;
}