#include <stdexcept>

template <typename T>
class Array2D {
private:
    T *array;
    unsigned int sizeX;
    unsigned int sizeY;

public:
    Array2D(unsigned int X, unsigned int Y) {
        sizeX = X;
        sizeY = Y;
        array = new T[X * Y];
    }

    ~Array2D() {
    delete[] array;
    }
    
    T& at(unsigned int X, unsigned int Y) {
        if((X > sizeX) || (Y > sizeY))
            throw std::out_of_range("Array2d out of range");

        return array[X * sizeX + Y];
    }
};