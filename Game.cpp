#include "Game.hpp"

#include <vector>
#include <fstream>
using std::vector;
using std::fstream;

Game::Game()
{
    board = new Board<point>(board_size);
    checked_board = new Board<bool>(board_size);
}
Game::~Game()
{
    delete board;
}
void Game::Start()
{
    captured = {-1, -1};
    game_status = started;
    Play();
}
void Game::Play()
{
    while(game_status != 0)
    {
        Position pos;
        PrintBoard();
        DetermineTurn();
        PlayerAction();
    }
}
void Game::DetermineTurn()
{
    if (active_player == 0){
        active_player = black;
        IO::TurnAnnouncement("black");
    } else if (active_player == black)
    {
        active_player = white;
        IO::TurnAnnouncement("white");
    } else if (active_player == white)
    {
        active_player = black;
        IO::TurnAnnouncement("black");
    }
}
void Game::PlayerAction()
{
    bool exit = false;
    Position pos;
    //run until valid input is entered
    while(!exit){
        int play = IO::PassOrPlay();
        if (play == 1)
        {
            bool valid = false;
            pos = IO::GetPosition(board_size);
            while(!valid){

                if( pos != captured && !(CheckSuicide(pos)) ){
                    valid = board->PlaceElem(pos, active_player);
                }
                
                if (!valid){
                    cout << "The piece cannot be placed in that location" << endl;
                    pos = IO::GetPosition(board_size);
                }
            }
            exit = true;
            
        } else if (play == 2)
        {
            HandleOptions();
        } else 
        {
            exit = true;
        }
    }
}
void Game::HandleOptions()
{
    int option = IO::Options();
    if (option == 1){
        LoadBoard();
    } else if (option == 2){
        SaveBoard();
    } 
}
bool Game::CheckSuicide(Position pos){
    checked_board->Clear();
    if(CheckSurrounded(pos, active_player))
    {
        //holds the array size for *enemies
        int num_enemies;
        point enemy = static_cast<point>(active_player * -1);
        Position *enemies = board->GetPositionsForElem(pos, enemy, num_enemies);
        //check capture of surrounding enemies
        for (size_t i; i < num_enemies; i++)
        {
            if(CheckCapture(enemies[i], enemy))
            {
                return false;
            }
        }
        //if execution arrives here all enemies are safe
        if (num_enemies == board->CountSurroundingPos(pos)){
            return true;
        }
        delete[] enemies;
        if(CheckCapture(pos, active_player))
        {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
bool Game::CheckCapture(Position pos, point piece)
{  
    if(CheckSurrounded(pos, piece))
    {
        int num_enemies;
        point enemy = static_cast<point>(piece * -1);
        Position *enemies = board->GetPositionsForElem(pos, enemy, num_enemies);
        if (num_enemies == board->CountSurroundingPos(pos)){
            return true;
        }
        delete[] enemies;
        if (CheckAllXForY(pos, piece, empty))
        {
            return false;
        }  else
        {
            return true;
        }     
        //look for first empty space amongst connected comrades
        
        return false;
    }
}

bool Game::CheckAllXForY(Position pos, point x, point y)
{
    if (!checked_board->CheckElem(pos))
    {
        int num_comrade;
        Position *comrades = board->GetPositionsForElem(pos, x, num_comrade);
        checked_board->PlaceElem(pos, true);
        for (int i; i < num_comrade; i++)
        {
            if (comrades[i]==y)
            {
                return true;
            }
            if (comrades[i]==x)
            {
                //check adjacencies
                if (CheckAllXForY(comrades[i], x, y)){
                    return true;
                }
            }
        }
        return false;
    } else {
        return false;
    }
}

bool Game::CheckSurrounded(Position pos, point piece)
{
    int num_pieces = 0;
    point *sur_pieces =  board->GetAllSurroundingElem(pos, num_pieces);
    for(int i; i < num_pieces;i++)
    {
        if(sur_pieces[i]==empty){
            return false;
        }
    }
    return true;
}
void Game::PrintBoard()
{
    for(int i = 0; i < board_size; i++)
    {
        point * lineElems = board->GetRowOfElem(i);
        string line = PointsToString(lineElems, board_size, false);
        delete[] lineElems;
        printLine(line);
    }
}
void Game::SaveBoard()
{
    fstream myfile;
    myfile.open ("save.txt", fstream::trunc);
    if (myfile.is_open()){
        for(int i = 0; i < board_size; i++)
        {
            point * lineElems = board->GetRowOfElem(i);
            string line = PointsToString(lineElems, board_size, true);
            delete[] lineElems;
            myfile << line << "\n";
        }
        myfile.close();
    }
}
void Game::LoadBoard()
{
    fstream myfile;
    myfile.open ("save.txt");
    if(myfile.is_open())
    {
        string line;
        int i = 0;
        while(getline(myfile, line))
        {
            point * p_row = StringToPoints(line, board_size);
            board->SetRowOfElem(p_row , i++);
        }
         myfile.close();
    }
   
}
string Game::PointsToString(point * points, int size, bool saving)
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

point * Game::StringToPoints(string point_string, int size)
{
    point * returning_points = new point[size];
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

void Game::ProcessTurn(Position pos)
{
    //process the consequences of the players turn
}
void Game::CalculateScore()
{
    //calculate final score
}
void Game::End()
{
    game_status = unstarted;
}