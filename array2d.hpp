#pragma once
#include <stdexcept>
#include "elements.hpp"
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
    unsigned int GetSize(){
        return size;
    }
    T& at(unsigned int i) {
        if(i > size) throw std::out_of_range("Array2d out of range");

        return array[i];
    }
    T& at(unsigned int x, unsigned int y) {
        if((x > sizeX) || (y > sizeY))
            throw std::out_of_range("Array2d out of range");

        return array[x * sizeX + y];
    }
    T& at(Position pos) {
        if((pos.x > sizeX) || (pos.y > sizeY))
            throw std::out_of_range("Array2d out of range");

        return array[pos.x * sizeX + pos.y];
    }
};