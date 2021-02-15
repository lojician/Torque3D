
#pragma once
#include <string>

enum point : int {empty = 0, black = 1, white = -1};
namespace PH{
    std::string PointsToString(point * points, int size, bool saving);
}

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
 BoundPosition &above = boundPositions[0] = {{0,-1}, false};
 BoundPosition &below = boundPositions[1] = {{0,1}, false};
 BoundPosition &left = boundPositions[2] = {{-1,0}, false};
 BoundPosition &right = boundPositions[3] = {{1,0}, false};;
};


struct SurroundingOffsets
{
    Position dir[4];
    const Position above = dir[0] = {0,-1};
    const Position below = dir[1] = {0,1};
    const Position left = dir[2] = {-1,0};
    const Position right = dir[3] = {1,0};
    
};
struct BoundaryChecker
{
    bool dir[4] = {true};
    bool &above = dir[0];
    bool &below = dir[1];
    bool &left = dir[2];
    bool &right = dir[3];
};

