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
template<typename V>
V util::combine(const V& vec1, const  V& vec2) 
{
    V ret_vec;
    ret_vec.reserve(vec1.size()+vec2.size());
    ret_vec.insert(ret_vec.end(), vec1.begin(), vec1.end());
    ret_vec.insert(ret_vec.end(), vec2.begin(), vec2.end());
    return ret_vec;
}
template<typename V>
void util::concat(V& v1, const V& v2) 
{
    v1.insert( v1.end(), v2.begin(), v2.end() );
}