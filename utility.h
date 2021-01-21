#include <stdexcept>

enum point {empty = 0, black = 1, white = 2, captured = 3};
enum gameStatus {unstarted = 0, started = 1, player_acting = 2, processing_action = 3};

template <typename T>
class Array2D {
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

    T& at(unsigned int X, unsigned int Y) {
        if((X > sizeX) || (Y > sizeY))
            throw std::out_of_range("Array2d out of range");

        return array[X * sizeX + Y];
    }
};