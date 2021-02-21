#include "Save.hpp"

//=================================
// included dependencies
#include "Board.hpp"
#include "UI.hpp"
#include "elements.hpp"
#include "MatchInfo.hpp"
#include <fstream>
#include <string>

//Aliases/namespace inclusions
using std::fstream;
using std::endl;

//initializing class variables
const string Save::GameSave = "save.game";
const string Save::BoardSave = "save";

/**
 * TODO: Add save file class that converts parameters from/to string
 * TODO: and can  be passed between Game and Save;
*/

void Save::SaveGame(Board<point>* board, MatchInfo* save)
{
    std::ofstream save_file (GameSave);
    //fstream save_file;
    //save_file.open ("save.txt", fstream::trunc);
    
    if (save_file.is_open()){
        //turn parameters to string and push on vector
        string first_line = save->GetSaveString();
        save_file << first_line << "\n";

        //Save the board state to rest of file
        for(int i = 0; i < save->board_size; i++)
        {
            vector<point> lineElems = board->GetRowOfElem(i);
            string line = PH::PointsToString(lineElems, save->board_size, true);
            save_file << line << "\n";
        }
        save_file.close();
    }
}

void Save::LoadGame(Board<point>* board, MatchInfo* save)
{
    fstream save_file;
    save_file.open (GameSave);
    if(save_file.is_open())
    {
        //get first line containing game stat info
        string first_line;
        getline(save_file, first_line);
        save->LoadSaveFile(first_line);
        //get and set the state of the board from rest of file
        string line;
        int i = 0;
        while(getline(save_file, line))
        {
            vector<point> p_row = StringToPoints(line, save->board_size);
            board->SetRowOfElem(p_row , i++);
        }
         save_file.close();
    }
}

void Save::SaveBoard(Board<point>* board, int board_size)
{
    std::ofstream save_file (BoardSave);
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
    save_file.open (BoardSave);
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