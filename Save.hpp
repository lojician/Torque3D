#pragma once

#include <string>
using std::string;
template <typename T>
class Board;
enum point : int;
class Save{
    private:

    public:
    static const string filename;
    static point * StringToPoints(string, int);
    static void LoadBoard(Board<point>*, int);
    static void SaveBoard(Board<point>*, int);
    static void LoadGame(Board<point>*, int, point);
    static void SaveGame(Board<point>*, int, point);
};