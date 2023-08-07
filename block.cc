#include <utility>
#include <stdexcept>
#include <vector>
#include <iostream>
#include "board.h"
#include "block.h"

using namespace std;

bool Block::checkBoard(const vector<pair<int, int>> &coords, Board &board)
{
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
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
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
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

Block::Block(char type, int level) : bottomLeft{3, 0}, type{type}, level{level}
{
    switch (type)
    {
    case 'I':
        coords.push_back({3, 0});
        coords.push_back({3, 1});
        coords.push_back({3, 2});
        coords.push_back({3, 3});
        break;
    case 'J':
        coords.push_back({3, 0});
        coords.push_back({3, 1});
        coords.push_back({3, 2});
        coords.push_back({2, 0});
        break;
    case 'L':
        coords.push_back({3, 0});
        coords.push_back({3, 1});
        coords.push_back({3, 2});
        coords.push_back({2, 2});
        break;
    case 'O':
        coords.push_back({3, 0});
        coords.push_back({3, 1});
        coords.push_back({2, 0});
        coords.push_back({2, 1});
        break;
    case 'S':
        coords.push_back({3, 0});
        coords.push_back({3, 1});
        coords.push_back({2, 1});
        coords.push_back({2, 2});
        break;
    case 'Z':
        coords.push_back({3, 1});
        coords.push_back({3, 2});
        coords.push_back({2, 0});
        coords.push_back({2, 1});
        break;
    case 'T':
        coords.push_back({3, 1});
        coords.push_back({2, 0});
        coords.push_back({2, 1});
        coords.push_back({2, 2});
        break;
    case '*':
        coords.push_back({0, 5});
        bottomLeft = {0, 5};
        break;
    default:
        throw runtime_error("Block creation was called on invalid character: " + type);
        break;
    }
}

void Block::rotate(bool clockwise, Board &board)
{
    if (coords.size() != 4)
    {
        throw runtime_error("you called rotate function on a block already dropped!");
    }
    vector<pair<int, int>> newCoords{coords.size()};
    pair<int, int> pivotOffset = {0, 0};
    // calculate the relative coordinate about (0,0)
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
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
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
    {
        int actualRow = newCoords[i].first + bottomLeft.first - pivotOffset.first;
        int actualCol = newCoords[i].second + bottomLeft.second - pivotOffset.second;
        newCoords[i] = {actualRow, actualCol};
    }

    if (!checkBounds(newCoords) || !checkBoard(newCoords, board))
    {
        return;
    }
    // update the coords
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
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
    vector<pair<int, int>> newCoords{coords.size()};
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
    {
        newCoords[i] = {coords[i].first + shift.first, coords[i].second + shift.second};
    }

    if (!checkBounds(newCoords) || !checkBoard(newCoords, board))
    {
        return;
    }
    // update the coords
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
    {
        coords[i] = newCoords[i];
    }
    bottomLeft = {bottomLeft.first + shift.first,
                  bottomLeft.second + shift.second};
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
            for (int i = 0; i < static_cast<int>(coords.size()); i++)
            {
                newCoords[i].first++;
            }
        }
        if (shift > 0)
        {
            for (int i = 0; i < static_cast<int>(coords.size()); i++)
            {
                coords[i].first += (shift - 1);
            }
            bottomLeft.first += (shift - 1);
        }
    }
}

const vector<pair<int, int>> &Block::getCoords() const
{
    return coords;
}

void Block::ShiftCoords(int r, int c)
{
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
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

void Block::deleteCoord(int row, int col)
{
    for (auto it = coords.begin(); it != coords.end();)
    {
        if ((*it).first == row && (*it).second == col)
        {
            it = coords.erase(it);
        }
        else
        {
            it++;
        }
    }
};

// assumes we have the coordinate and we can shift down
// used for shifting rows down
void Block::shiftDownCoord(int row, int col)
{
    for (int i = 0; i < static_cast<int>(coords.size()); i++)
    {
        if (coords[i].first == row && coords[i].second == col)
        {
            coords[i].first++;
            return;
        }
    }
}

int Block::GetLevel() const
{
    return level;
}
