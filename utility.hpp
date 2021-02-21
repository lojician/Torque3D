#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;


//Add common items to namespace

namespace util{
    vector<string> getStringParts(string str, char delim = ' ') 
    { 
        vector<string> parts;
        string word = ""; 
        int i = 0;
        for (auto x : str)  
        { 
            if (x == delim) 
            { 
                parts.push_back(word);
                word = ""; 
            } 
            else { 
                word = word + x; 
            } 
        } 
        return parts;
    } 
}


