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
    Position * GetAllSurroundingPositions(Position, int&);
    Position * GetPositionsForElem(Position, T, int&);
    T * GetAllSurroundingElem(Position, int&);
    T GetOffsetPiece(Position, Position);
    bool CheckOffset(Position, Position);
    bool CheckOffsetForElem(Position, Position, T);
    

};