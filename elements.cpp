#include "elements.hpp"
bool operator==(point& p, int i)
{
    return (p == static_cast<point>(i));
}
point operator*(point& p, int i)
{
    return static_cast<point>(static_cast<int>(p) * i);
}

string PH::PointsToString(vector<point> points, int size, bool saving)
{
    string return_string  = "";

    for(int i = 0; i < size; i++){

        if (points[i] == point::white){
            return_string += "w";
        } else if (points[i] == point::black){
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
    for (int i = 0; i < size; i++) {
        if(point_string[i] == 'b'){
            returning_points[i] = point::black;
        } else if(point_string[i] == 'w'){
            returning_points[i] = point::white;
        } else {
            returning_points[i] = point::empty;
        }
    }
    return returning_points;

}