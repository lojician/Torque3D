#include "Board.hpp"
template <class T>
Board<T>::Board(int x)
{
    //initialize grid and make sure it's clear
    size = x;
    grid = new Array2D<T>(size,size);
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
T Board<T>::CheckRelative(Position pos, char axi, int offset)
{
    
}

template <class T>
Board<T>::~Board()
{
    delete[] grid;
}
template class Board<point>;