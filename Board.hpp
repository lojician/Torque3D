#pragma once
#include "utility.h"
template <typename T>
class Board
{ 
    
private:
    /* data */
    int size;
    Array2D<T> *grid;
    
    
public:
    Board(int);
    ~Board();
    bool PlacePiece(Position, T);
    void RemovePiece(Position);
    void Clear();
    T PointCheck(Position);
    

};