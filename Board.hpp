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
    bool PlacePiece(Position, point);
    bool CheckCapture(Position, point);
    void RemovePiece(Position);
    void Clear();
    point PointCheck(Position);
    

};