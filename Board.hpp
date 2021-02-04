#pragma once
#include "utility.h"
template <typename T>
class Board
{ 
    
private:
    /* data */
    int size;
    Array2D<T> *grid;
    Array2D<bool> *checked;
    
public:
    Board(int);
    ~Board();
    bool PlacePiece(Position, T);
    void RemovePiece(Position);
    T PointCheck(Position);
    void Clear();
    int CountSurroundingOf(Position, T);
    BoundaryChecker BoundsCheck(Position);
    Position * GetAllSurroundingPositions(Position);
    T * GetAllSurroundingElem(Position);
    Position * GetPositionsForElem(Position, T, size_t&);
    T GetOffsetPiece(Position, Position);
    bool CheckOffsetPiece(Position, Position, T&);
    

};