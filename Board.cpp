#include "Board.hpp"
template <class T>
Board<T>::Board(int x)
{
    //initialize grid and make sure it's clear
    size = x;
    grid = new Array2D<T>(size,size);
    checked = new Array2D<bool>(size, size);
    Clear();
}

template <class T>
bool Board<T>::PlacePiece(Position pos, T piece)
{
    if (grid->at(pos) == empty){
        //add logic to make sure piece would not be taken
        grid->at(pos) = piece;
        return true;
    } else {
        return false;
    }
}

template <class T>
void Board<T>::RemovePiece(Position pos)
{
    grid->at(pos) = empty;
}

template <class T>
void Board<T>::Clear()
{
    grid->clear();
}

template <class T>
T Board<T>::PointCheck(Position pos)
{
    return grid->at(pos);
}

template <class T>
int Board<T>::CountSurroundingOf(Position pos, T piece)
{
    SurroundingOffsets sur_pos;
    T sur_elem[4];
    int i = 0;
    SBPosition bounded_pos;
    BoundaryChecker inbounds = BoundsCheck(pos);
    
    if(inbounds.below)
    {
        if (CheckOffsetElem(pos, sur_pos.below, piece))
        {
            i++;
        }
    } 
    if(inbounds.above)
    {
        if (CheckOffsetElem(pos, sur_pos.above, piece))
        {
            i++;
        }
    } 
    if(inbounds.right)
    {
        if (CheckOffsetElem(pos, sur_pos.right, piece))
        {
            i++;
        }
    } 
    if(inbounds.left)
    {
        if (CheckOffsetElem(pos, sur_pos.left, piece))
        {
            i++;
        }
    }
    return i;
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
T * Board<T>::GetAllSurroundingElem(Position pos)
{
    /* SurroundingOffsets sur_pos;
    T sur_elem[4];
    int i = 0;
    if(pos.y == 0){
        if (GetOffsetPiece(pos, sur_pos.below, sur_elem[i]))
        {
            i++;
        }
       
    } else if(pos.y == (size -1)){
        if (GetOffsetPiece(pos, sur_pos.above, sur_elem[i]))
        {
            i++;
        }
    } else {
        if (GetOffsetPiece(pos, sur_pos.above, sur_elem[i]))
        {
            i++;
        }
        if (GetOffsetPiece(pos, sur_pos.below, sur_elem[i]))
        {
            i++;
        }
    }
    if(pos.x == 0){
        if (GetOffsetPiece(pos, sur_pos.right, sur_elem[i]))
        {
            i++;
        }
    } else if(pos.x == (size -1)){
        if (GetOffsetPiece(pos, sur_pos.left, sur_elem[i]))
        {
            i++;
        }
    }else {
        if (GetOffsetPiece(pos, sur_pos.right, sur_elem[i]))
        {
            i++;
        }
        if (GetOffsetPiece(pos, sur_pos.left, sur_elem[i]))
        {
            i++;
        }
    }
    T returning_elems[(i-1)];
    for (int j = 0; j<i; j++){
        returning_elems[j] = sur_elem[j];
    }
    return returning_elems; */
}

template <class T>
Position * Board<T>::GetPositionsForElem(Position pos, T piece, size_t& arraySize)
{
    SurroundingOffsets sur_pos;
    Position sur_elem_pos[4];
    int i = 0;
    if(pos.y == 0){
        sur_elem_pos[i++] = sur_pos.below;
       
    } else if(pos.y == (size -1)){
        sur_elem_pos[i++] = sur_pos.above;
    } else {
        sur_elem_pos[i++] = sur_pos.below;
        sur_elem_pos[i++] = sur_pos.above;
    }
    if(pos.x == 0){
        sur_elem_pos[i++] = sur_pos.right;
    } else if(pos.x == (size -1)){
        sur_elem_pos[i++] = sur_pos.left;
    }else {
        sur_elem_pos[i++] = sur_pos.right;
        sur_elem_pos[i++] = sur_pos.left;
    }
    arraySize = (i);
    Position* returning_elems = new Position[(i-1)];
    for (int j = 0; j<i; j++){
        returning_elems[j] = sur_elem_pos[j];
    }
    //make sure to delete
    return returning_elems;
}

template <class T>
T Board<T>::GetOffsetPiece(Position pos, Position offset)
{
    pos += offset;
    return PointCheck(pos);  
}

template <class T>
bool Board<T>::CheckOffsetElem(Position pos, Position offset, T elem)
{ 
    pos += offset;
    if(!(checked->at(pos)) && (PointCheck(pos) == elem))
    {
        return true;    
    } else {
        return false;
    }
}

template <class T>
Board<T>::~Board()
{
    delete[] grid;
}
template class Board<point>;
template class Board<bool>;