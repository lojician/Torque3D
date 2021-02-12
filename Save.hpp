#pragma once
#include "Board.hpp"
#include "UI.hpp"
class Save{
private:

public:
    static point * StringToPoints(string, int);
    static void LoadBoard(Board<point>*, int);
    static void SaveBoard(Board<point>*, int);
    static void LoadGame(Board<point>*, int, point);
    static void SaveGame(Board<point>*, int, point);
}