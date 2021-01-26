#pragma once
#include "utility.h"
class Input
{
private:
    
public:
    static char GetCharInput(string);
    static string GetStringInput(string);
    static int GetIntInput(string);
    static bool PassOrPlay();
    static Position GetPosition(int);
};