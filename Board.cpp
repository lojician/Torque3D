#include "Board.hpp"

Board::Board(int x)
{
    //initialize grid and make sure it's clear
    size = x;
    grid = new Array2D<point>(size,size);
    Board::Clear();
}

bool Board::PlacePiece(Position pos, point piece)
{
    if (grid->at(pos) == empty){
        grid->at(pos) = piece;
        return true;
    } else if (grid->at(pos) == captured) {
        //check if single piece captured
        return false;
    } else {
        return false;
    }
}
void Board::RemovePiece(Position pos)
{
     grid->at(pos) = empty;
}
void Board::Clear()
{
    grid->clear();
}
point Board::PointCheck(Position pos)
{
 return grid->at(pos);
}


Board::~Board()
{
    delete[] grid;
}