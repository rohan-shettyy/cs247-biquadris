#include <iostream>

#include "biquadrisgame.h"
#include <vector>
#include <utility>
#include "board.h"
#include "block.h"

using namespace std;

int main(int argc, char **argv)
{
    int level = 0;
    string scriptfile1 = "sequence1.txt";
    string scriptfile2 = "sequence2.txt";
    bool textOnly = false;
    int seed = 1;
    for (int i = 0; i < argc; i++)
    {
        string arg = argv[i];
        if (arg == "-text")
        {
            textOnly = true;
        }
        else if (arg == "-seed")
        {
            seed = stoi(argv[i + 1]);
        }
        else if (arg == "-scriptfile1")
        {
            scriptfile1 = argv[i + 1];
        }
        else if (arg == "-scriptfile2")
        {
            scriptfile2 = argv[i + 1];
        }
        else if (arg == "-startlevel")
        {
            level = stoi(argv[i + 1]);
        }
    }
    srand(seed);
    ifstream in;
    BiquadrisGame game{in, scriptfile1, scriptfile2, level, textOnly};
    game.Init();
}
