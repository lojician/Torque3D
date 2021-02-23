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
vector<point> PH::StringToPoints(string point_string, int size)
{
    vector<point> returning_points = vector<point>(size);
    for (int i; i < size; i++) {
        if(point_string[i] == 'b'){
            returning_points[i] = black;
        } else if(point_string[i] == 'w'){
            returning_points[i] = white;
        } else {
            returning_points[i] = empty;
        }
    }
    return returning_points;

}