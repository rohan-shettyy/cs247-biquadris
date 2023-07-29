#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

using namespace std;

class ScoreManager
{
    static int hiScore;
    int score;
public:
    void update(int, int);

    const int GetScore() const;
};

#endif
