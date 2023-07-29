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
    void rotate(bool);
    void shift(char);
    void drop(Board &);
    vector<pair<int, int>> &getCoords();
    pair<int, int> &getLeft()
    {
        return bottomLeft;
    }
};

#endif