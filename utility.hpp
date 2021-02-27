#pragma once
#include <vector>
#include <string>
using std::vector;
using std::string;

//Add common items to namespace

namespace util{
    vector<string> getStringParts(string str, char delim = ',');
    
    template <typename V> 
    V combine(const V& vec1, const V& vec2);
    template <typename V> 
    void concat(V& vec1, const V& vec2);
}

template <typename T>
std::vector<T> operator+(const std::vector<T> &A, const std::vector<T> &B)
{
    std::vector<T> AB;
    AB.reserve(A.size() + B.size());                // preallocate memory
    AB.insert(AB.end(), A.begin(), A.end());        // add A;
    AB.insert(AB.end(), B.begin(), B.end());        // add B;
    return AB;
}

template <typename T>
std::vector<T> &operator+=(std::vector<T> &A, const std::vector<T> &B)
{
    A.reserve(A.size() + B.size());                // preallocate memory without erase original data
    A.insert(A.end(), B.begin(), B.end());         // add B;
    return A;                                        // here A could be named AB
}
