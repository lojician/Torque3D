#pragma once
#include "utility.h"
class IO
{
private:
    static const string invalid_input;
    static const string error_oor;
public:
    static char StartEntry();
    static char GetCharInput(string);
    static string GetStringInput(string);
    static int GetIntInput(string);
    static bool PassOrPlay();
    template <typename T> 
    static T GetInput(T);
    static Position GetPosition(int);
    static void TurnAnnouncement(string);
};