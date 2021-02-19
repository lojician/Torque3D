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
    T GetElem(Position);
    bool CheckPosFor(Position, T);
    bool CheckIfEdge(Position);
    void Clear();
    void SetEdges();
    vector<T> GetRowOfElem(int);
    void SetRowOfElem(vector<T>, int);
    int CountSurroundingOf(Position, T);
    int CountSurroundingPos(Position);
    BoundaryChecker BoundsCheck(Position);
    SBPosition BoundsCheckSB(Position);
    vector<Position> GetAllSurrPos(Position);
    vector<Position> GetPosForSurrElems(Position, T);
    vector<T> GetAllSurroundingElem(Position);
    vector<Position> GetAllPosForElem(T);
    T GetOffsetPiece(Position, Position);
    bool CheckOffset(Position, Position);
    bool CheckOffsetForElem(Position, Position, T);

};