#ifndef PUZZLE_H
#define PUZZLE_H


#pragma once

#include <iostream>
#include <math.h>
#include <ctime>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
#include <functional>
using namespace std;

class puzzle
{
private:
    int fl_size = 0;
    vector<int> fl;
    int empty_place = 0;
    int Game_status = 0;

public:
    int getSize();
    int getEmpty();
    vector<int> getState();
    void setState(vector<int>);
    puzzle(int size);
    void move(int c_i, int c_j);
    vector<int> move(vector<int> fl_c, int diff);
    int status();
    int isGame();
    void shuffle();
    int heuristic(vector<int> state);
    vector<vector<int>> solve();

};
#endif // PUZZLE_H
