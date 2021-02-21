#include "Save.hpp"

//=================================
// included dependencies
#include "Board.hpp"
#include "UI.hpp"
#include "elements.hpp"
#include "Game.hpp"
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
vector<string> Save::getStringParts(string str, char seperator) 
{ 
    vector<string> parts;
    string word = ""; 
    int i = 0;
    for (auto x : str)  
    { 
        if (x == seperator) 
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
void Save::SaveGame(Board<point>* board, int board_size, point active_player, bool passed, int blacks_caps, int white_caps)
{
    std::ofstream save_file (GameSave);
    //fstream save_file;
    //save_file.open ("save.txt", fstream::trunc);
    
    if (save_file.is_open()){
        //turn parameters to string and push on vector
        vector<string> stringified;
        stringified.push_back(std::to_string(board_size));
        stringified.push_back(std::to_string(active_player));
        stringified.push_back(std::to_string(passed));
        stringified.push_back(std::to_string(blacks_caps));
        stringified.push_back(std::to_string(white_caps));

        //Add parameters to first line of file
        string first_line;
        for (auto& x : stringified) {
            x+=" ";
            first_line += x;
        }
        save_file << first_line << "n";

        //Save the board state to rest of file
        for(int i = 0; i < board_size; i++)
        {
            vector<point> lineElems = board->GetRowOfElem(i);
            string line = PH::PointsToString(lineElems, board_size, true);
            save_file << line << "\n";
        }
        save_file.close();
    }
}

void Save::LoadGame(Board<point>* board, Game* game)
{
    fstream save_file;
    save_file.open (GameSave);
    if(save_file.is_open())
    {
        //get first line containing game stat info
        string first_line;
        getline(save_file, first_line);
        vector<string> state_strings = getStringParts(first_line, ' ');
        int i = 0;
        int board_size = std::stoi(state_strings[i++]);
        point ap = static_cast<point>(std::stoi(state_strings[i++]));
        bool passed = std::stoi(state_strings[i++]);
        int black_caps = std::stoi(state_strings[i++]);
        int white_caps = std::stoi(state_strings[i++]);
        game->SetGameParameters(board_size, ap, passed, black_caps, white_caps);

        //get and set the state of the board from rest of file
        string line;
        i = 0;
        while(getline(save_file, line))
        {
            vector<point> p_row = StringToPoints(line, board_size);
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