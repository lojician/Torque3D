#pragma once
//=================================
// included dependencies
#include <string>
using std::string;
//=================================
// forward declared dependencies
template <typename T>
class Board;
enum point : int;
struct Position;
class UI
{
private:
    static const string invalid_input;
    static const string error_oor;
    
public:
    static void ClearBuffer();
    static void PrintLine(string);
    static char GetCharInput(string);
    static string GetStringInput(string);
    static int GetIntInput(string);
    static char GetValidChar(char[], int, string);
    static char StartEntry();
    static char PlayMenu();
    static char Options();
    template <typename T> 
    static T GetInput(T);
    static Position GetPosition(int);
    static void TurnAnnouncement(string);
    static void PrintBoard(Board<point>*, int);
    static string PointsToString(point *, int, bool);

};