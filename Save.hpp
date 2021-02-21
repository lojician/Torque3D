#pragma once
#include "utility.hpp"
template <typename T>
class Board;
enum point : int;
class MatchInfo;
class Save{
    private:

    public:
    static const string BoardSave;
    static const string GameSave;
    static vector<point> StringToPoints(string, int);
    static void LoadBoard(Board<point>*, int);
    static void SaveBoard(Board<point>*, int);
    static void LoadGame(Board<point>*, MatchInfo*);
    static void SaveGame(Board<point>* board, MatchInfo*);
};