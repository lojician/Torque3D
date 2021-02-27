#pragma once
#include "utility.hpp"
template <typename T>
class Board;
enum class point : char;
class MatchInfo;
class Save{
    private:
    static const string save_name;
    static int save_slots;
    public:
    static void LoadGame (MatchInfo*);
    static void SaveGame(MatchInfo*);
    static vector<string> BoardToStrs(Board<point>*, int);
    static void LoadBoard(Board<point>*, int, vector<string>);
    static void SaveFile(string name, vector<string> contents);
    static vector<string> LoadFile(string name);

};