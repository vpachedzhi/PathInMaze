#pragma once

#include <iostream>
#include <stack>
#include <string>
#include <list>

#include "Board.h"
//#include "PathFinder.h"
using namespace std;


stack<Cell*> aStar(Board& board,Cell* start,Cell* end);



