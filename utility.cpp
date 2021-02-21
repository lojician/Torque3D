#include "utility.hpp"
vector<string> util::getStringParts(string str, char delim)
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