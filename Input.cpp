#include "Input.hpp"

const string IO::invalid_input =  "Invalid input. Try Again.";
const string IO::error_oor = "The location is outside the valid range.";

char IO::StartEntry()
{
    //entry Question
    string entryQ = "q to quit, s to start";
    //entry Response
    char entryR = GetCharInput(entryQ);
    return entryR;
}
string IO::GetStringInput(string output)
{
    printLine(output);
    string type;
    return GetInput(type);
}
char IO::GetCharInput(string output)
{
    printLine(output);
    char type;
    return GetInput(type);
}
int IO::GetIntInput(string output)
{
    printLine(output);
    int type;
    return GetInput(type);
}
template <typename T> 
T IO::GetInput(T input)
{
    while(!(cin >> input))
    {   
        clearBuffer();
        printLine(invalid_input);
    }
    clearBuffer();
    return input;
}
int IO::PassOrPlay()
{
    char input; 
    string pass_play_out = "To Take your turn enter t, to pass enter p to get more options enter o \n";  
    while (true){
        input = GetCharInput(pass_play_out);
        if (input == 't'){
            return 1;
        } else if (input == 'p')
        {
            return 0;
        } else if (input == 'o')
        {
            return 2;
        }
        else {
            printLine(invalid_input);
        }
    }
}
int IO::Options()
{
    char input; 
    string pass_play_out = "(l) to load board (s) to save game (e) to exit \n";  
    while (true){
        input = GetCharInput(pass_play_out);
        if (input == 'l'){
            return 1;
        } else if (input == 's')
        {
            return 2;
        } else if (input == 'e')
        {
            return 0;
        }
        else {
            printLine(invalid_input);
        }
    }
}
Position IO::GetPosition(int board_size)
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
            printLine(error_oor);
            pos.x = GetIntInput(col_req);
        } else if(pos.y < 0 && pos.y >= board_size){ 
            printLine(error_oor);
            pos.y = GetIntInput(row_req);
        }
    }
}
void IO::TurnAnnouncement(string player)
{
    string AnnounceTurn = "It is " + player + " turn to act.";
    printLine(AnnounceTurn);
}
