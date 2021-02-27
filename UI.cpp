
#include "UI.hpp"

//=================================
// included dependencies
#include "Board.hpp"
#include "elements.hpp"
// for cin/cout
#include<iostream>
// for <streamsize>
#include<ios>
// for numeric_limits
#include<limits>
//for find
#include <algorithm>




//Aliases/namespace inclusions
using std::cout;
using std::cin;
using std::string;
using std::endl;
//using std::find ,std::begin, std::end;

//initializing class variables
const string UI::invalid_input =  "Invalid input. Try Again.";
const string UI::error_oor = "The location is outside the valid range.";

void UI::ClearBuffer()
{
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}
void UI::PrintLine(string out)
{
    cout << out << endl;
}



string UI::GetStringInput(string output)
{
    PrintLine(output);
    string type="";
    return GetInput(type);
}
char UI::GetCharInput(string output)
{
    PrintLine(output);
    char type=0;
    return GetInput(type);
}
int UI::GetIntInput(string output)
{
    PrintLine(output);
    int type=0;
    return GetInput(type);
}
template <typename T>
T UI::GetInput(T input)
{
    while(!(cin >> input))
    {
        ClearBuffer();
        PrintLine(invalid_input);
    }
    ClearBuffer();
    return input;
}
char UI::GetValidChar(char valid_in[], int size, string output)
{
    char input;
    while (true){
            input = GetCharInput(output);
            if (std::find(valid_in, valid_in + size, input))
            {
                return input;
            }
            else {
                PrintLine(invalid_input);
            }
        }
}

void UI::PrintBoard(Board<point> *board, int board_size)
{
    for(int i = 0; i < board_size; i++)
    {
        vector<point>  lineElems = board->GetRowOfElem(i);
        string line = PH::PointsToString(lineElems, board_size, false);
        PrintLine(line);
    }
}
string UI::GetPointString(point p)
{
    if (p == point::black)
    {
        return "Black";
    } else if (p == point::white) {
        return "White";
    }
    return "none";
}

char UI::StartEntry()
{
    //entry Question
    string entryQ = "q to quit, s to start";
    //entry Response
    char valid_in[] = {'q', 's'};
    return GetValidChar(valid_in, sizeof(valid_in), entryQ);
}
char UI::PlayMenu()
{
    string pass_play_out = "To Take your turn enter t, to pass enter p to get more options enter o \n";
    char valid_in[] = {'t', 'p','o'};
    return GetValidChar(valid_in, sizeof(valid_in), pass_play_out);
}
char UI::Options()
{
    string opt_out = "(l) to load board (s) to save game (e) to exit \n";
    char valid_in[] = {'l', 's','e'};
    return GetValidChar(valid_in, sizeof(valid_in), opt_out);
}

Position UI::GetPosition(int board_size)
{
    bool valid = false;
    Position pos;
    string col_req = "Enter colunm number: ";
    string row_req = "Enter row number: ";
    while(true)
    {
        //cout << "Enter the colunm and row number from 0 to " << (board_size - 1) << "\n";
        //place piece where player specified
        pos.x = GetIntInput(col_req);
        pos.y = GetIntInput(row_req);
        if ((pos.x >= 0 && pos.x < board_size)&&(pos.y >= 0&& pos.y < board_size)){
            return pos;
        } else if(pos.x < 0 && pos.x >= board_size){
            PrintLine(error_oor);
            pos.x = GetIntInput(col_req);
        } else if(pos.y < 0 && pos.y >= board_size){
            PrintLine(error_oor);
            pos.y = GetIntInput(row_req);
        }
    }
}

void UI::TurnAnnouncement(string player)
{
    string AnnounceTurn = "It is " + player + " turn to act.";
    PrintLine(AnnounceTurn);
}

void UI::PrintPlayersScore(int i_score, point player_in)
{
    string player = GetPointString(player_in);
    string score =  std::to_string(i_score);
    PrintLine(player + " has " + score + " caps.");
}

void UI::PrintFinalScores(int i_black_score, int i_white_score)
{
    string black_score = std::to_string(i_black_score);
    string white_score = std::to_string(i_white_score);
    PrintLine("Black has " + black_score + " points.");
    PrintLine("White has " + white_score + " points.");
}

