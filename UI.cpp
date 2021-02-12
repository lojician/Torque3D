#include "UI.hpp"
#include <algorithm>  
//using std::find ,std::begin, std::end;

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
    string type;
    return GetInput(type);
}
char UI::GetCharInput(string output)
{
    PrintLine(output);
    char type;
    return GetInput(type);
}
int UI::GetIntInput(string output)
{
    PrintLine(output);
    int type;
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
        point * lineElems = board->GetRowOfElem(i);
        string line = PointsToString(lineElems, board_size, false);
        delete[] lineElems;
        PrintLine(line);
    }
}

string UI::PointsToString(point * points, int size, bool saving)
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
