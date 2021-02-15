#pragma once
#include <vector>
//=================================
// forward declared dependencies
template <typename T> class Array2D;
struct Position;
struct BoundaryChecker;
struct SBPosition;

template <typename T>
class Board
{ 
    
private:
    /* data */
    int size;
    int x,y;
    Array2D<T> *grid;
    std::vector<std::vector<bool>> edge;
    
public:
    Board(int);
    ~Board();
    bool PlaceElem(Position, T);
    void RemoveElem(Position);
    T CheckElem(Position);
    bool CheckIfEdge(Position);
    void Clear();
    void SetEdges();
    T * GetRowOfElem(int);
    void SetRowOfElem(T*, int);
    int CountSurroundingOf(Position, T);
    int CountSurroundingPos(Position);
    BoundaryChecker BoundsCheck(Position);
    SBPosition BoundsCheckSB(Position);
    Position * GetAllSurroundingPositions(Position, int&);
    Position * GetPositionsForElem(Position, T, int&);
    T * GetAllSurroundingElem(Position, int&);
    T GetOffsetPiece(Position, Position);
    bool CheckOffset(Position, Position);
    bool CheckOffsetForElem(Position, Position, T);

};