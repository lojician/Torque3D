#pragma once
#include <vector>
//=================================
// forward declared dependencies
using std::vector;
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
    vector<T> GetRowOfElem(int);
    void SetRowOfElem(vector<T>, int);
    int CountSurroundingOf(Position, T);
    int CountSurroundingPos(Position);
    BoundaryChecker BoundsCheck(Position);
    SBPosition BoundsCheckSB(Position);
    vector<Position> GetAllSurroundingPositions(Position);
    vector<Position> GetPositionsForElem(Position, T);
    vector<T> GetAllSurroundingElem(Position);
    T GetOffsetPiece(Position, Position);
    bool CheckOffset(Position, Position);
    bool CheckOffsetForElem(Position, Position, T);

};