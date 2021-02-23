#include "MatchInfo.hpp"
#include "Save.hpp"
#include "Board.hpp"

MatchInfo::MatchInfo(int b_size)
{
    board_size = b_size;
    active_player = empty;
    board = new Board<point>(board_size);
}
MatchInfo::~MatchInfo()
{
    delete board;
}
string MatchInfo::GetSaveString() 
{
    vector<string> stringified;
    stringified.push_back(std::to_string(board_size));
    stringified.push_back(std::to_string(active_player));
    stringified.push_back(std::to_string(passed_last_turn));
    stringified.push_back(std::to_string(blacks_caps));
    stringified.push_back(std::to_string(whites_caps));
    stringified.push_back(captured.get_string(delim));
    string save_string;
    for (auto& x : stringified) {
        x+=delim;
        save_string += x;
    }
    return save_string;
}
void MatchInfo::LoadSaveFile(string state_info) 
{
    vector<string> state_strings = util::getStringParts(state_info, delim);
    int i = 0;
    board_size = std::stoi(state_strings[i++]);
    active_player = static_cast<point>(std::stoi(state_strings[i++]));
    passed_last_turn = std::stoi(state_strings[i++]);
    blacks_caps = std::stoi(state_strings[i++]);
    whites_caps = std::stoi(state_strings[i++]);
    captured = {(std::stoi(state_strings[i++])), (std::stoi(state_strings[i++]))};
}

void MatchInfo::SaveGame() 
{
    vector<string> save;
    string first_line = GetSaveString();
    save.push_back(first_line);
    vector<string> board_lines = Save::BoardToStrs(board, board_size);
    save += board_lines;
    Save::SaveFile("GameSave", save);
}

void MatchInfo::LoadGame() 
{
    auto save_file = Save::LoadFile("GameSave");
    LoadSaveFile(save_file[0]);
    save_file.erase(save_file.begin());
    Save::LoadBoard(board, board_size, save_file);
}


