#pragma once
//=================================
// included dependencies

//=================================
// forward declared dependencies
template <typename T> class Array2D;
struct Position;
struct BoundaryChecker;
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
    T * GetRowOfElem(int);
    void SetRowOfElem(T*, int);
    int CountSurroundingOf(Position, T);
    int CountSurroundingPos(Position);
    BoundaryChecker BoundsCheck(Position);
    Position * GetAllSurroundingPositions(Position, int&);
    Position * GetPositionsForElem(Position, T, int&);
    T * GetAllSurroundingElem(Position, int&);
    T GetOffsetPiece(Position, Position);
    bool CheckOffset(Position, Position);
    bool CheckOffsetForElem(Position, Position, T);

};