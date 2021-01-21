#pragma once
#include "utility.h"


// TODO: Create Board class
//*b

class Board
{ 
    
private:
    /* data */
    int size;
    Array2D<point> *grid;
    
public:
    Board(int);
    ~Board();
    void PlacePiece(int, int, point);
    void RemovePiece(int, int);
    void Clear();
    point PointCheck(int, int);
    

};