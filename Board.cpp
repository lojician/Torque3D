#include "Board.hpp"

//=================================
// included dependencies
#include "array2d.hpp"
#include "elements.hpp"

template <class T>
Board<T>::Board(int x)
{
    //initialize grid and make sure it's clear
    size = x;
    grid = new Array2D<T>(size, size);
    edge = std::vector<std::vector<bool>>(size, std::vector<bool>(size, false));
    SetEdges();
    Clear();
}
template <class T>
Board<T>::~Board()
{
    delete[] grid;
}

template <class T>
bool Board<T>::PlaceElem(Position pos, T elem)
{
    if (grid->at(pos) == 0){
        grid->at(pos) = elem;
        return true;
    } else {
        return false;
    }
}
template <>
bool Board<point>::PlaceElem(Position pos, point elem)
{
    if (grid->at(pos) == point::empty) {
        grid->at(pos) = elem;
        return true;
    }
    else {
        return false;
    }
}
template <class T>
void Board<T>::RemoveElem(Position pos)
{
    grid->at(pos) = 0;
}
template <>
void Board<point>::RemoveElem(Position pos)
{
    grid->at(pos) = point::empty;
}
template <class T>
void Board<T>::Clear()
{
    grid->clear();
}

template <class T>
void Board<T>::SetEdges()
{
    //Mark positions at the edge of the board as so
    int max = size-1;
    for(unsigned int i = 0; i < size; i++)
    {
        edge[0][i] = true;
        edge[max][i] = true;
        edge[i][0] = true;
        edge[i][max] = true;
    }
    edge;
}

template <class T>
T Board<T>::GetElem(Position pos)
{
    return grid->at(pos);
}

template <typename T>
bool Board<T>::CheckPosFor(Position pos, T elem)
{
    if (GetElem(pos) == elem){
        return true;
    } else {
        return false;
    }
}
template <class T>
bool Board<T>::CheckIfEdge(Position pos)
{
    return edge[pos.x][pos.y];
}
template <class T>
vector<T> Board<T>::GetRowOfElem(int row)
{
   vector<T> returning_elems = vector<T>(size);
    for (unsigned int i = 0; i < size; i++){
        returning_elems[i] = grid->at(i,row);
    }
    return returning_elems;
}
template <class T>
void Board<T>::SetRowOfElem(vector<T> elem_row, int row)
{
    for (unsigned int i = 0; i < size; i++){
        grid->at(i,row) = elem_row[i];
    }
}
template <class T>
int Board<T>::CountSurroundingOf(Position pos, T elem)
{
    //count the number of a
    int count = 0;
    if (CheckIfEdge(pos)){
        SBPosition inboundpos = BoundsCheckSB(pos);
        for (int i = 0; i<4;i++)
        {
            if (inboundpos.boundPositions[i].inbounds)
            {
                if (CheckOffsetForElem(pos, inboundpos.boundPositions[i].pos, elem))
                {
                    count++;
                }
            }
        }
        return count;
    }
    for (size_t  i = 0; i < 4; i++){
        SurroundingOffsets sur_pos;
        if (CheckOffsetForElem(pos, sur_pos.dir[i], elem))
            {
                count++;
            }
    }
    return count;
}

template <class T>
int Board<T>::CountSurroundingPos(Position pos)
{
    //count the number of valid positions around a given position
    if (CheckIfEdge(pos)){
        int count = 0;
        BoundaryChecker inbounds = BoundsCheck(pos);

        for(auto x : inbounds.dir)
        {
            if(x)
            {
                count++;
            }
        }
        return count;
    } else {
        return 4;
    }
}


template <class T>
vector<Position> Board<T>::GetAllSurrPos(Position pos)
{
    SurroundingOffsets sur_pos;
    Position sur_elem_pos[4];
    int size = 0;
    if(pos.y == (size -1)){
        sur_elem_pos[size++] = sur_pos.above;

    } else if(pos.y == 0){
        sur_elem_pos[size++] = sur_pos.below;
    } else {
        sur_elem_pos[size++] = sur_pos.above;
        sur_elem_pos[size++] = sur_pos.below;
    }
    if(pos.x == (size -1)){
        sur_elem_pos[size++] = sur_pos.left;
    } else if(pos.x == 0){
        sur_elem_pos[size++] = sur_pos.right;
    }else {
        sur_elem_pos[size++] = sur_pos.left;
        sur_elem_pos[size++] = sur_pos.right;
    }
    vector<Position>  returning_positions = vector<Position>(size);
    for (size_t i = 0; i<size; i++){
        returning_positions[i] = sur_elem_pos[i];
    }
    //make sure to delete
    return returning_positions;
}

template <class T>
vector<Position> Board<T>::GetPosForSurrElems(Position pos, T elem)
{
    Position sur_elem_pos[4];
    int count = 0;
    if (CheckIfEdge(pos)){
        SBPosition inboundpos = BoundsCheckSB(pos);
        for (size_t i = 0; i<4;i++)
        {
            if (inboundpos.boundPositions[i].inbounds)
            {
                if (CheckOffsetForElem(pos, inboundpos.boundPositions[i].pos, elem))
                {
                    sur_elem_pos[count++] = pos + inboundpos.boundPositions[i].pos;
                }
            }
        }
    } else {
        SurroundingOffsets sur_pos;
        for (size_t  i = 0; i < 4; i++){
            SurroundingOffsets sur_pos;
            if (CheckOffsetForElem(pos, sur_pos.dir[i], elem))
                {
                    sur_elem_pos[count++] = pos + sur_pos.dir[i];
                }
        }
    }
    vector<Position> returning_positions = vector<Position>(count);
    for (size_t  i = 0; i<count; i++){
        returning_positions[i] = sur_elem_pos[i];
    }
    //make sure to delete
    return returning_positions;
}

template <class T>
vector<T> Board<T>::GetAllSurroundingElem(Position pos)
{
    SurroundingOffsets sur_pos;
    T sur_elem[4] = {static_cast<T>(0)};
    int arraySize = 0;
    BoundaryChecker inbounds = BoundsCheck(pos);

    if(inbounds.above)
    {
        sur_elem[arraySize++] = GetOffsetPiece(pos, sur_pos.above);

    }
    if(inbounds.below)
    {
         sur_elem[arraySize++] = GetOffsetPiece(pos, sur_pos.below);
    }
    if(inbounds.left)
    {
        sur_elem[arraySize++] = GetOffsetPiece(pos, sur_pos.left);
    }
    if(inbounds.right)
    {
         sur_elem[arraySize++] = GetOffsetPiece(pos, sur_pos.right);
    }

    vector<T> returning_elems = vector<T>(arraySize);
    for (size_t i = 0; i<arraySize; i++)
    {
        returning_elems[i] = sur_elem[i];
    }
    //make sure to delete
    return returning_elems;
}

template <typename T>
vector<Position> Board<T>::GetAllPosForElem(T elem)
{
    vector<Position> matching_elems;
    for(int i = 0; i < grid->GetSize(); i++)
    {
        if (grid->at(i) == elem){
            Position pos = Position({i/size, i%size});
            matching_elems.push_back(pos);
        }
    }
    return matching_elems;
}


template <class T>
T Board<T>::GetOffsetPiece(const Position pos,const Position offset)
{
    Position offset_pos = pos + offset;
    return GetElem(offset_pos);
}

template <class T>
bool Board<T>::CheckOffset(Position pos, Position offset)
{
    pos += offset;
    if((GetElem(pos) != static_cast<T>(0)))
    {
        return true;
    } else {
        return false;
    }
}
template <class T>
bool Board<T>::CheckOffsetForElem(Position pos, Position offset, T elem)
{
    pos += offset;
    return CheckPosFor(pos, elem);
}

template <class T>
BoundaryChecker Board<T>::BoundsCheck(Position pos)
{
    BoundaryChecker check;
    if(pos.y == 0){
        check.above = false;
        check.below = true;

    } else if(pos.y == (size -1)){
        check.above = true;
        check.below = false;
    } else {
        check.above = true;
        check.below = true;
    }
    if(pos.x == 0){
        check.left = false;
        check.right = true;
    } else if(pos.x == (size -1)){
        check.left = true;
        check.right = false;
    }else {
        check.left = true;
        check.right = true;
    }
    return check;
}
template <class T>
SBPosition Board<T>::BoundsCheckSB(Position pos)
{
    SBPosition check;
    if(pos.y == 0){
        check.above.inbounds = false;
        check.below.inbounds  = true;

    } else if(pos.y == (size -1)){
        check.above.inbounds  = true;
        check.below.inbounds  = false;
    } else {
        check.above.inbounds  = true;
        check.below.inbounds  = true;
    }
    if(pos.x == 0){
        check.left.inbounds  = false;
        check.right.inbounds  = true;
    } else if(pos.x == (size -1)){
        check.left.inbounds  = true;
        check.right.inbounds  = false;
    }else {
        check.left.inbounds  = true;
        check.right.inbounds  = true;
    }
    return check;
}
template class Board<point>;
template class Board<bool>;