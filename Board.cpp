#include "Board.hpp"

Board::Board(int x)
{
    size = x;
    grid = new Array2D<point>(size,size);
    Board::Clear();
}

void Board::PlacePiece(int x, int y, point piece){
    if (grid->at(x,y) == empty){
        grid->at(x,y) = piece;
    } else if (grid->at(x,y) == captured) {
        //check if single piece captured
    }
}
void Board::RemovePiece(int x, int y){
     grid->at(x,y) = empty;
}
void Board::Clear(){
    grid->clear();
}
point Board::PointCheck(int x, int y){
 return grid->at(x,y);
}


Board::~Board()
{
    delete[] grid;
}