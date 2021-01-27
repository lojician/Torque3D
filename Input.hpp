#pragma once
#include "utility.h"
class Input
{
private:
    
public:
    static char GetCharInput(std::string);
    static std::string GetStringInput(std::string);
    static int GetIntInput(std::string);
    static bool PassOrPlay();
    static Position GetPosition(int);
};