#ifndef BLOCK_H
#define BLOCK_H

#include <utility>

class Board;

using namespace std;

class Block
{
private:
    vector<pair<int, int>> coords;
    pair<int, int> bottomLeft;
    char type;
    int level;

public:
    int orientation = 0;
    bool isHeavy = false;

    // Constructor
    Block(char, int);
    bool checkBoard(const vector<pair<int, int>> &coords, Board &board);
    bool checkBounds(const vector<pair<int, int>> &coords);
    void rotate(bool, Board &);
    void shift(char, Board &);
    void drop(Board &);
    const vector<pair<int, int>>& getCoords() const;
    void ShiftCoords(int, int);
    const char GetType() const;
    pair<int, int> getLeft() const;
};

#endif