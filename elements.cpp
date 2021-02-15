#include "elements.hpp"
string PH::PointsToString(vector<point> points, int size, bool saving)
{
    string return_string  = "";
    
    for(int i = 0; i < size; i++){
        
        if (points[i] == white){
            return_string += "w";
        } else if (points[i] == black){
            return_string += "b";
        } else {
            return_string += "'";
        }
        //don't add seperator when saving out to file
        if(!saving){
            return_string += "|";
        }
    }

    return return_string;
}