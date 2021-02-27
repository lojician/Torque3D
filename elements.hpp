
#pragma once
#include <string>
#include <vector>

using std::vector;
using std::string;

enum class point : char {empty = 0, black = 1, white = -1};
bool operator==(point& p, int i);
point operator*(point& p, int i);

namespace PH{
    string PointsToString(vector<point> points, int size, bool saving);
    vector<point> StringToPoints(string point_string, int size);
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
    vector<string> get_vstring() const{
        vector<string> vs_pos;
        vs_pos.push_back(std::to_string(x));
        vs_pos.push_back(std::to_string(y));
        return vs_pos;
    }
    string get_string(const char delim = ' ') const{
        string s_pos;
        s_pos+=std::to_string(x);
        s_pos+=delim;
        s_pos+=std::to_string(y);
        return s_pos;
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
    bool dir[4] = {false};
    bool &above = dir[0];
    bool &below = dir[1];
    bool &left = dir[2];
    bool &right = dir[3];
};

