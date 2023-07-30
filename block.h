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
    // Constructor
    Block(char, int);
    void rotate(bool, Board &);
    void shift(char, Board &);
    void drop(Board &);
    const vector<pair<int, int>> &getCoords() const;
    const char GetType() const;
    pair<int, int> &getLeft()
    {
        return bottomLeft;
    }
};

#endif