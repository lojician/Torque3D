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
    bool PlaceElem(Position, T);
    void RemoveElem(Position);
    T CheckElem(Position);
    void Clear();
    int CountSurroundingOf(Position, T);
    BoundaryChecker BoundsCheck(Position);
    Position * GetAllSurroundingPositions(Position, int&);
    Position * GetPositionsForElem(Position, T, int&);
    T * GetAllSurroundingElem(Position, int&);
    T GetOffsetPiece(Position, Position);
    bool CheckOffset(Position, Position);
    bool CheckOffsetForElem(Position, Position, T);
    void setPosChecked()
    

};