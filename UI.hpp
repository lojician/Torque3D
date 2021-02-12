#pragma once
#include "utility.h"
#include "Board.hpp"
class UI
{
private:
    static const string invalid_input;
    static const string error_oor;
    
public:
    static char StartEntry();
    static char GetCharInput(string);
    static string GetStringInput(string);
    static int GetIntInput(string);
    static char GetValidChar(char[], int, string);
    static void PrintBoard(Board<point>*, int);
    static string PointsToString(point *, int, bool);
    static char PlayMenu();
    static char Options();
    template <typename T> 
    static T GetInput(T);
    static Position GetPosition(int);
    static void TurnAnnouncement(string);

};