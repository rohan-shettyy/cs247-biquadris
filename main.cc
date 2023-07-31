#include <iostream>

#include "biquadrisgame.h"
#include <vector>
#include <utility>
#include "board.h"
#include "block.h"

using namespace std;

void printBlock(Block &s, vector<vector<char>> &grid, vector<pair<int, int>> &coords)
{
    cout << "Printing grid" << endl;
    coords = s.getCoords();
    grid = vector<vector<char>>(18, vector<char>(11, '_'));
    for (auto c : coords)
    {
        grid[c.first][c.second] = 'X';
    }
    for (int i = 0; i < 18; i++)
    {
        for (int j = 0; j < 11; j++)
        {
            cout << grid[i][j] << " ";
        }
        cout << endl;
    }
}

int main(int argc, char **argv)
{
    // Board board = Board();
    // Block s = Block('S', 1);

    // vector<vector<char>> grid;
    // vector<pair<int, int>> coords;

    // printBlock(s, grid, coords);
    // s.rotate(true);
    // printBlock(s, grid, coords);

    /*s.rotate(false);
    cout << "grid: clockwise" << endl;
    printBlock(s, grid, coords);*/
    ifstream in;
    BiquadrisGame game = BiquadrisGame(in);
    game.Init();
}
