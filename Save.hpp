#pragma once
#include "Board.hpp"
#include "UI.hpp"
class Save{
private:

public:
    static point * StringToPoints(string, int);
    static void LoadBoard();
    static void SaveBoard();
    static void LoadGame();
    static void SaveGame();
}