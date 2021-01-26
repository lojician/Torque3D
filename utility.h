#pragma once

#include <stdexcept>
#include <iostream>
// for <streamsize> 
#include<ios>      
// for numeric_limits 
#include<limits>  

//Aliases for common functions
auto& cin = std::cin;
auto& cout = std::cout;
void clearBuffer(){
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}

enum point {empty = 0, black = 1, white = 2, captured = 3};
enum gameStatus {unstarted = 0, started = 1, player_acting = 2, processing_action = 3};
struct Position
{
    unsigned int x = 0;
    unsigned int y = 0;
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