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
const string Save::save_name = "save.game";


 //TODO: Add save slots


void Save::SaveGame(MatchInfo* match)
{
    vector<string> save;
    string first_line = match->GetSaveString();
    save.push_back(first_line);
    vector<string> board = BoardToStrs(match->board, match->board_size);
    save += board;
    SaveFile(save_name, save);
}

void Save::LoadGame(MatchInfo* match)
{
    auto save_file = LoadFile(save_name);
    match->LoadSaveFile(save_file[0]);
    save_file.erase(save_file.begin());
    LoadBoard(match->board, match->board_size, save_file);
}

vector<string> Save::BoardToStrs(Board<point>* board, int board_size)
{
    vector<string> board_strings;
    board_strings.reserve(board_size);
    for(int i = 0; i < board_size; i++)
    {
        vector<point> lineElems = board->GetRowOfElem(i);
        string line = PH::PointsToString(lineElems, board_size, true);
        board_strings.push_back(line);
    }
    return board_strings;
}
void Save::LoadBoard(Board<point>* board, int board_size, vector<string> board_lines)
{
    int i = 0;
    for (auto& line : board_lines)
    {
        vector<point> p_row = PH::StringToPoints(line, board_size);
        board->SetRowOfElem(p_row , i++);
    }
   
}

void Save::SaveFile(string name, vector<string> contents) 
{
    std::ofstream save_file (name);
    //fstream save_file;
    //save_file.open ("save.txt", fstream::trunc);
    
    if (save_file.is_open()){
        for(auto& line : contents)
        {
            save_file << line << endl;
        }
        save_file.close();
    }
}

vector<string> Save::LoadFile(string name) 
{
    vector<string> contents;
    fstream save_file;
    save_file.open (name);
    if(save_file.is_open())
    {
        string line;
        while(getline(save_file, line))
        {
            contents.push_back(line);
        }
         save_file.close();
    }
}
