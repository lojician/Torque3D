#pragma once
#include "utility.hpp"
template <typename T>
class Board;
enum point : int;
class Game;
class Save{
    private:

    public:
    static const string BoardSave;
    static const string GameSave;
    static vector<point> StringToPoints(string, int);
    static vector<string> getStringParts(string str, char seperator=' ');
    static void LoadBoard(Board<point>*, int);
    static void SaveBoard(Board<point>*, int);
    static void LoadGame(Board<point>*, Game*);
    static void SaveGame(Board<point>* board, int board_size, point active_player, bool passed, int blacks_caps, int white_caps);
};