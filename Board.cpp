#include "Board.hpp"

Board::Board(int x)
{
    //initialize grid and make sure it's clear
    size = x;
    grid = new Array2D<point>(size,size);
    Board::Clear();
}

void Board::PlacePiece(Position pos, point piece)
{
    if (grid->at(pos) == empty){
        grid->at(pos) = piece;
    } else if (grid->at(pos) == captured) {
        //check if single piece captured
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