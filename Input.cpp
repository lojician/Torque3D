#include "Input.hpp"
char IO::StartEntry(){
    //entry Question
    string entryQ = "q to quit, s to start";
    printLine(entryQ);
    //entry Response
    char entryR = getchar();
    

}
string IO::GetStringInput(string output)
{
    printLine(output);
    string input;
    cin >> input;
    return input;
}
char IO::GetCharInput(string output)
{
    printLine(output);
    char input;
    cin >> input;
    while(!cin.fail())
    {   
        clearBuffer();
        cout<< "You have entered wrong input.\n";
        cin >> input;
    }
    clearBuffer();
    return input;
}
int IO::GetIntInput(string output)
{
    cout << output;
    int input;
    cin >> input;
    while(!cin.fail())
    {   
        clearBuffer();
        cout<< "You have entered wrong input.\n";
        cin >> input;
    }
    clearBuffer();
    return input;
}

bool IO::PassOrPlay()
{
    char input; 
    string pass_play_out = "Do you want to play(p), or skip(s)\n";  
    while (true){
        input = GetCharInput(pass_play_out);
        if (input == 'p'){
            return true;
        } else if (input == 's')
        {
            return false;
        }
        else {
            cout << "Invalid input: " << input << "\n";
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
        if ((pos.x >= 0&& pos.x < board_size)&&(pos.y >= 0&& pos.y < board_size)){
            return pos;
        } else if(pos.x < 0&& pos.x >= board_size){ 
            cout << "The location is outside the valid range\n";
            pos.x = GetIntInput(col_req);
        } else if(pos.y < 0&& pos.y >= board_size){ 
            cout << "The location is outside the valid range\n";
            pos.y = GetIntInput(row_req);
        }
    }
}
void IO::TurnAnnouncement(string player)
{
    cout << "It is " << player <<" turn to act." << endl;
}
