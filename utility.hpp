#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;


//Add common items to namespace

namespace util{
    vector<string> getStringParts(string str, char delim = ',');
}


