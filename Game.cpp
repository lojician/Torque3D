#include "Game.hpp"

//=================================
// included dependencies
#include "UI.hpp"
#include "Save.hpp"
#include "Board.hpp"
#include "elements.hpp"
/* #include <vector>

using std::vector; */

//initialize 
Game::Game()
{
    board_size = 9;
    active_player = empty;
    game_status = unstarted;
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
        UI::PrintBoard(board, board_size);
        DetermineTurn();
        PlayerAction();
    }
}
void Game::DetermineTurn()
{
    if (active_player == 0){
        active_player = black;
        UI::TurnAnnouncement("black");
    } else if (active_player == black)
    {
        active_player = white;
        UI::TurnAnnouncement("white");
    } else if (active_player == white)
    {
        active_player = black;
        UI::TurnAnnouncement("black");
    }
}
void Game::PlayerAction()
{
    bool exit = false;
    Position pos;
    //run until valid input is entered
    while(!exit){
        char play = UI::PlayMenu();
        if (play == 't')
        {
            bool valid = false;
            pos = UI::GetPosition(board_size);
            while(!valid){

                if( pos != captured && !(CheckSuicide(pos)) ){
                    valid = board->PlaceElem(pos, active_player);
                }
                
                if (!valid){
                    UI::PrintLine("The piece cannot be placed in that location");
                    pos = UI::GetPosition(board_size);
                }
            }
            exit = true;
            
        } else if (play == 'o')
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
    char option = UI::Options();
    if (option == 'l'){
        Save::LoadBoard(board, board_size);
    } else if (option == 's'){
        Save::SaveBoard(board, board_size);
    } 
}

bool Game::CheckSuicide(Position pos){
    checked_board->Clear();
    bool check = CheckSurrounded(pos, active_player);
    if(check)
    {
        point enemy = static_cast<point>(active_player * -1);
        vector<Position> enemies = board->GetPositionsForElem(pos, enemy);
        //check capture of surrounding enemies
        for (size_t i = 0 ; i < enemies.size(); i++)
        {
            board->PlaceElem(pos, active_player);
            if(CheckCapture(enemies[i], enemy))
            {
                board->RemoveElem(pos);
                return false;
            }
        }
        //if execution arrives here all enemies are safe
        if (enemies.size() == board->CountSurroundingPos(pos)){
            return true;
        }
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

bool Game::CheckSurrounded(Position pos, point piece)
{
    vector<point> sur_pieces =  board->GetAllSurroundingElem(pos);
    for(int i = 0; i < sur_pieces.size();i++)
    {
        if(sur_pieces[i]==empty){
            return false;
        }
    }
    return true;
}

bool Game::CheckCapture(Position pos, point piece)
{  
    if(CheckSurrounded(pos, piece))
    {
        //look for first empty space amongst connected comrades
        
        point enemy = static_cast<point>(piece * -1);
        vector<Position> enemies = board->GetPositionsForElem(pos, enemy);
        if (enemies.size() == board->CountSurroundingPos(pos)){
            return true;
        }
        if (CheckAllXForY(pos, piece, empty))
        {
            return false;
        }  else
        {
            return true;
        }     
        return false;
    }
    return false;
}

bool Game::CheckAllXForY(Position pos, point x, point y)
{
    if (!checked_board->CheckElem(pos))
    {
        vector<Position> comrades = board->GetPositionsForElem(pos, x);
        checked_board->PlaceElem(pos, true);
        for (int i; i < comrades.size(); i++)
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