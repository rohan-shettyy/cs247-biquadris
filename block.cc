#include <utility>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "biquadrisgame.h"
#include "board.h"
#include "block.h"

using namespace std;

bool Block::checkBoard(const vector<pair<int, int>> &coords, Board &board)
{
    for (int i = 0; i < 4; i++)
    {
        int row = coords[i].first;
        int col = coords[i].second;
        if (board.GetGrid()[row][col].first != ' ')
        {
            return false;
        }
    }
    return true;
}

bool Block::checkBounds(const vector<pair<int, int>> &coords)
{
    for (int i = 0; i < 4; i++)
    {
        int row = coords[i].first;
        int col = coords[i].second;
        if (row < 0 || row >= 18 || col < 0 || col >= 11)
        {
            return false; // we make no modification
        }
    }
    return true;
}

Block::Block(char type, int level) : coords{{-1, -1}, {-1, -1}, {-1, -1}, {-1, -1}}, bottomLeft{3, 0}, type{type}, level{level}
{
    switch (type)
    {
    case 'I':
        coords[0] = {3, 0};
        coords[1] = {3, 1};
        coords[2] = {3, 2};
        coords[3] = {3, 3};
        break;
    case 'J':
        coords[0] = {3, 0};
        coords[1] = {3, 1};
        coords[2] = {3, 2};
        coords[3] = {2, 0};
        break;
    case 'L':
        coords[0] = {3, 0};
        coords[1] = {3, 1};
        coords[2] = {3, 2};
        coords[3] = {2, 2};
        break;
    case 'O':
        coords[0] = {3, 0};
        coords[1] = {3, 1};
        coords[2] = {2, 0};
        coords[3] = {2, 1};
        break;
    case 'S':
        coords[0] = {3, 0};
        coords[1] = {3, 1};
        coords[2] = {2, 1};
        coords[3] = {2, 2};
        break;
    case 'Z':
        coords[0] = {3, 1};
        coords[1] = {3, 2};
        coords[2] = {2, 0};
        coords[3] = {2, 1};
        break;
    case 'T':
        coords[0] = {3, 1};
        coords[1] = {2, 0};
        coords[2] = {2, 1};
        coords[3] = {2, 2};
        break;
    default:
        break;
    }
}

void Block::rotate(bool clockwise, Board &board)
{
    vector<pair<int, int>> newCoords{4};
    pair<int, int> pivotOffset = {0, 0};

    // calculate the relative coordinate about (0,0)
    for (int i = 0; i < 4; i++)
    {
        // coordinate if bottom left is (0,0)
        int relRow = (coords[i].first - bottomLeft.first);
        int relCol = (coords[i].second - bottomLeft.second);
        if (clockwise)
        {
            pivotOffset = {max(pivotOffset.first, relRow), max(pivotOffset.second, relCol)};
            int temp = relRow;
            relRow = relCol;
            relCol = -1 * temp;
        }
        else
        {
            pivotOffset = {min(pivotOffset.first, relRow), min(pivotOffset.second, relCol)};
            int temp = relRow;
            relRow = -1 * relCol;
            relCol = temp;
        }
        newCoords[i] = {relRow, relCol};
    }
    // rotate the newPivot
    if (clockwise)
    {
        int temp = pivotOffset.first;
        pivotOffset.first = pivotOffset.second;
        pivotOffset.second = -1 * temp;
    }
    else
    {
        int temp = pivotOffset.first;
        pivotOffset.first = -1 * pivotOffset.second;
        pivotOffset.second = temp;
    }
    // calculate the actual location of coordinates
    for (int i = 0; i < 4; i++)
    {
        int actualRow = newCoords[i].first + bottomLeft.first - pivotOffset.first;
        int actualCol = newCoords[i].second + bottomLeft.second - pivotOffset.second;
        newCoords[i] = {actualRow, actualCol};
    }

    if (!checkBounds(newCoords) || !checkBoard(newCoords, board))
    {
        // return;
    }
    // update the coords
    for (int i = 0; i < 4; i++)
    {
        coords[i] = newCoords[i];
    }
    // update the orientation
    if (clockwise)
    {
        orientation = (orientation + 1) % 4;
    }
    else
    {
        orientation = (orientation + 3) % 4;
    }

    if (board.GetLevel() >= 3)
    {
        shift('d', board);
    }
}

void Block::shift(char direction, Board &board)
{
    pair<int, int> shift;
    switch (direction)
    {
    case 'r':
        shift = {0, 1};
        break;
    case 'l':
        shift = {0, -1};
        break;
    case 'u':
        shift = {-1, 0};
        break;
    case 'd':
        shift = {1, 0};
        break;
    default:
        throw runtime_error("Invalid shift direction got: " + direction);
    }
    vector<pair<int, int>> newCoords{4};
    for (int i = 0; i < 4; i++)
    {
        newCoords[i] = {coords[i].first + shift.first, coords[i].second + shift.second};
    }

    if (!checkBounds(newCoords) || !checkBoard(newCoords, board))
    {
        return;
    }
    // update the coords
    for (int i = 0; i < 4; i++)
    {
        coords[i] = newCoords[i];
    }
    bottomLeft = {bottomLeft.first + shift.first,
                  bottomLeft.second + shift.second};

    if (direction == 'r' || direction == 'l')
    {
        if (board.isHeavy)
        {
            pair<int, int> currLeft = getLeft();
            this->shift('d', board);
            this->shift('d', board);
            if (getLeft().first - currLeft.first < 2)
            {
                board.GetGame().cmdManager->CallCommand(board, "drop");
            }
        }
        else if (board.GetLevel() >= 3)
        {
            this->shift('d', board);
        }
    }
}

void Block::drop(Board &board)
{
    if (checkBounds(coords) && checkBoard(coords, board))
    {
        int shift = 0;
        vector<pair<int, int>> newCoords = coords;
        while (checkBounds(newCoords) && checkBoard(newCoords, board))
        {
            shift++;
            for (int i = 0; i < 4; i++)
            {
                newCoords[i].first++;
            }
        }
        if (shift > 0)
        {
            for (int i = 0; i < 4; i++)
            {
                coords[i].first += (shift - 1);
            }
            bottomLeft.first += (shift - 1);
        }
    }
}

const vector<pair<int, int>>& Block::getCoords() const
{
    return coords;
}

void Block::ShiftCoords(int r, int c)
{
    for (int i = 0; i < 4; i++)
    {
        coords[i].first += r;
        coords[i].second += c;
    }
    bottomLeft.first += r;
    bottomLeft.second += c;
}

const char Block::GetType() const
{
    return type;
}

pair<int, int> Block::getLeft() const
{
    return bottomLeft;
}