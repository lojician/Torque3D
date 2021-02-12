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

enum point {empty = 0, black = 1, white = -1};
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

    bool operator!=(const Position& other) const {
        return (x != other.x || y != other.y);
    }

    bool operator==(const Position& other) const {
        return (x == other.x && y == other.y);
    }

};
struct BoundPosition
{
   Position pos;
   bool inbounds;
};

//surrounding bound positions
struct SBPosition
{
 BoundPosition boundPositions[4];
 BoundPosition &above = boundPositions[0];
 BoundPosition &below = boundPositions[1];
 BoundPosition &left = boundPositions[2];
 BoundPosition &right = boundPositions[3];
};


struct SurroundingOffsets
{
    const Position above = {0,-1};
    const Position below = {0,1};
    const Position left = {-1,0};
    const Position right = {1,0};
    
};
struct BoundaryChecker
{
    bool dir[4] = {true};
    bool &above = dir[0];
    bool &below = dir[1];
    bool &left = dir[2];
    bool &right = dir[3];
};

//Array 2D taken fron stackoverflow
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
            array[i] = static_cast<T>(0);
        }
    }

    T& at(Position pos) {
        if((pos.x > sizeX) || (pos.y > sizeY))
            throw std::out_of_range("Array2d out of range");

        return array[pos.x * sizeX + pos.y];
    }
};