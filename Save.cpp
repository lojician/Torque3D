#include "Save.hpp"

//=================================
// included dependencies
#include "Board.hpp"
#include "UI.hpp"
#include "elements.hpp"
#include <fstream>
#include <string>

//Aliases/namespace inclusions
using std::fstream;

//initializing class variables
const string Save::filename = "save";

void Save::LoadGame(Board<point>* board, int board_size, point active_player)
{

}
void Save::SaveGame(Board<point>* board, int board_size, point active_player)
{

}
void Save::SaveBoard(Board<point>* board, int board_size)
{
    std::ofstream save_file (filename);
    //fstream save_file;
    //save_file.open ("save.txt", fstream::trunc);
    if (save_file.is_open()){
        for(int i = 0; i < board_size; i++)
        {
            vector<point> lineElems = board->GetRowOfElem(i);
            string line = PH::PointsToString(lineElems, board_size, true);
            save_file << line << "\n";
        }
        save_file.close();
    }
}
void Save::LoadBoard(Board<point>* board, int board_size)
{
    fstream save_file;
    save_file.open (filename);
    if(save_file.is_open())
    {
        string line;
        int i = 0;
        while(getline(save_file, line))
        {
            vector<point> p_row = StringToPoints(line, board_size);
            board->SetRowOfElem(p_row , i++);
        }
         save_file.close();
    }
   
}
vector<point> Save::StringToPoints(string point_string, int size)
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