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
    whites_caps = 0;
    blacks_caps = 0;
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
                
                if(pos != captured)
                {
                    if (board->PlaceElem(pos, active_player))
                    {
                        bool suicide =CheckSuicide(pos);
                        if (!suicide)
                        {
                            valid = true;
                            ProcessAction(pos);

                        } else 
                        {
                            board->RemoveElem(pos);
                        }
                    }
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
    if(CheckSurrounded(pos, active_player))
    {
        //check surrounding friends for free space
        auto friends_positions = board->GetPositionsForElem(pos, active_player);
        checked_board->Clear();
        for (size_t i = 0 ; i < friends_positions.size(); i++)
        {
            if(CheckAllXForY(friends_positions[i], active_player, empty)){
                return false;
            }
        }

        point enemy = static_cast<point>(active_player * -1);
        auto enemy_positions = board->GetPositionsForElem(pos, enemy);
        
        //check capture of surrounding enemies
        for (size_t i = 0 ; i < enemy_positions.size(); i++)
        {
            
            if(CheckCapture(enemy_positions[i], enemy))
            {
                return false;
            }
        }
        
        return true;

        // //if execution arrives here all enemies are safe --h
        // if (enemy_positions.size() == board->CountSurroundingPos(pos)){
        //     return true;
        // }
        // if(CheckCapture(pos, active_player))
        // {
        //     return true;
        // } else {
        //     return false;
        // }
    } else {
        return false;
    }
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
        checked_board->Clear();
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

bool Game::CheckAllXForY(Position pos, point x, point y)
{
    if (!checked_board->CheckElem(pos))
    {
        vector<Position> target = board->GetPositionsForElem(pos, y);
        if (target.size() > 0){
            return true;
        }
        vector<Position> comrades = board->GetPositionsForElem(pos, x);
        checked_board->PlaceElem(pos, true);
        for (int i = 0; i < comrades.size(); i++)
        {
            //check adjacencies
            if (CheckAllXForY(comrades[i], x, y)){
                return true;
            }
        }
        return false;
    } else {
        return false;
    }
}

void Game::CaptureAllConnected(Position pos, point point)
{
    vector<Position> comrades = board->GetPositionsForElem(pos, point);
    board->RemoveElem(pos);

    if (point == black){
        whites_caps += 1;
    } else if (point == white){
        blacks_caps += 1;
    }else {
        UI::PrintLine("somthing's wrong");
    }

    for (int i = 0; i < comrades.size(); i++)
    {
        CaptureAllConnected(comrades[i], point);
    }
}

void Game::ProcessAction(Position pos)
{
    //process the consequences of the players turn
    point enemy = static_cast<point>(active_player * -1);
    vector<Position> enemies = board->GetPositionsForElem(pos, enemy);
    for (size_t i = 0 ; i < enemies.size(); i++)
    {
        if(board->CheckElem(enemies[i]) == enemy){
            if(CheckCapture(enemies[i], enemy)){
                CaptureAllConnected(enemies[i], enemy);
            }
        }
    }
    int score;
    if (active_player == black){
        score = blacks_caps;
    } else if(active_player == white){
        score = whites_caps;
    }
    UI::PrintPlayersScore(score, active_player);
}
void Game::CalculateScore()
{
    //calculate final score
}
void Game::End()
{
    game_status = unstarted;
}