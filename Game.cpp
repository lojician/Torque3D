#include "Game.hpp"

#include <vector>
using std::vector;

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
    bool valid = false;
    Position pos;
    //run until valid input is entered
    bool play = IO::PassOrPlay();
    if (play)
    {
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
        if (num_enemies == 4){
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
        if (num_enemies == 4){
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
        string line = PointsToString(lineElems, board_size);
        delete[] lineElems;
        printLine(line);
    }
}
string Game::PointsToString(point * points, int size)
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
        return_string += "|";
    }
    return return_string;
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