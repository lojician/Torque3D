#pragma once

#include <stdexcept>
#include <iostream>
// for <streamsize> 
#include<ios>      
// for numeric_limits 
#include<limits>  

//Add common items to namespace
using std::cout;
using std::cin;
using std::string;
using std::endl;

//using string = std::string;
void clearBuffer();
void printLine(string);

enum point {empty = 0, black = 1, white = 2};
enum gameStatus {unstarted = 0, started = 1, player_acting = 2, processing_action = 3};
struct Position
{
    int x = 0;
    int y = 0;

    // default + parameterized constructor
    Position(int x=0, int y=0) 
        : x(x), y(y)
    {
    }
    
    Position operator+=(const Position& a)
    {
        x += a.x;
        y += a.y;
        return *this;
    }
    
    Position operator+(const Position& a) const
    {
        return Position(a.x+x, a.y+y);
    }

    

    bool operator==(const Position& other) const {
        return x == other.x && y == other.y;
    }

};
struct SurroundingPositions
{
   Position above = {0,-1};
   Position below = {0,-1};
   Position right = {0,-1};
   Position left = {0,-1};
};
//Array 2D taking fron
template <typename T>
class Array2D 
{
private:
    T *array;
    unsigned int sizeX;
    unsigned int sizeY;
    unsigned int size;

public:
    Array2D(unsigned int X, unsigned int Y) {
        sizeX = X;
        sizeY = Y;
        size =  X * Y;
        array = new T[size];
    }

    ~Array2D() {
        delete[] array;
    }
   
    void clear(){
        int i;
    
        for (i = 0; i < size; ++i)
        {
            array[i] = empty;
        }
    }

    T& at(Position pos) {
        if((pos.x > sizeX) || (pos.y > sizeY))
            throw std::out_of_range("Array2d out of range");

        return array[pos.x * sizeX + pos.y];
    }
};