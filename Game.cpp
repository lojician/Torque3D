#include "Game.hpp"

//=================================
// included dependencies
#include "UI.hpp"
#include "GameState.hpp"
#include "Board.hpp"
#include "elements.hpp"
/* #include <vector>

using std::vector; */

//initialize 
Game::Game()
{
    start_bias = 6;
    match.board_size = 9;
    match.active_player = empty;
    game_status = unstarted;
    board = new Board<point>(match.board_size);
    checked_board = new Board<bool>(match.board_size);
}
Game::~Game()
{
    delete board;
}
void Game::Start()
{
    match.captured = {-1, -1};
    game_status = started;
    match.whites_caps = 0;
    match.blacks_caps = 0;
    match.passed_last_turn = false;
    controlling_player = empty;
    Play();
}
void Game::Play()
{
    while(game_status == 1)
    {
        Position pos;
        UI::PrintBoard(board, match.board_size);
        DetermineTurn();
        PlayerAction();
    }
    if (game_status == ending)
    {
        End();
    }
}
void Game::End()
{
    game_status = unstarted;
    CalculateScore();
}
void Game::DetermineTurn()
{
    if (match.active_player == 0){
        match.active_player = black;
        UI::TurnAnnouncement("black");
    } else if (match.active_player == black)
    {
        match.active_player = white;
        UI::TurnAnnouncement("white");
    } else if (match.active_player == white)
    {
        match.active_player = black;
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
            match.passed_last_turn = false;
            bool valid = false;
            pos = UI::GetPosition(match.board_size);
            while(!valid){
                
                if(pos != match.captured)
                {
                    if (board->PlaceElem(pos, match.active_player))
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
                    pos = UI::GetPosition(match.board_size);
                }
            }
            exit = true;
            
        } else if (play == 'o')
        {
            HandleOptions();
        } else 
        {
            if (match.passed_last_turn){
                game_status = ending;
            }
            match.passed_last_turn = true;
            exit = true;
        }
    }
}

void Game::HandleOptions()
{
    char option = UI::Options();
    if (option == 'l'){
        Save::LoadGame(board, save);
    } else if (option == 's'){
        Save::SaveGame(board, board_size, active_player, passed_last_turn, blacks_caps, whites_caps);
    } 
}

bool Game::CheckSuicide(Position pos){
    if(CheckSurrounded(pos, match.active_player))
    {
        //check surrounding friends for free space
        auto friends_positions = board->GetPosForSurrElems(pos, match.active_player);
        checked_board->Clear();
        for (size_t i = 0 ; i < friends_positions.size(); i++)
        {
            if(CheckAllXForY(friends_positions[i], match.active_player, empty)){
                return false;
            }
        }

        point enemy = static_cast<point>(match.active_player * -1);
        auto enemy_positions = board->GetPosForSurrElems(pos, enemy);
        
        //check capture of surrounding enemies
        for (size_t i = 0 ; i < enemy_positions.size(); i++)
        {
            
            if(CheckCapture(enemy_positions[i], enemy))
            {
                return false;
            }
        }
        
        return true;
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
        vector<Position> enemies = board->GetPosForSurrElems(pos, enemy);
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
    if (!checked_board->GetElem(pos))
    {
        vector<Position> target = board->GetPosForSurrElems(pos, y);
        if (target.size() > 0){
            return true;
        }
        vector<Position> comrades = board->GetPosForSurrElems(pos, x);
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
    vector<Position> comrades = board->GetPosForSurrElems(pos, point);
    board->RemoveElem(pos);

    if (point == black){
        match.whites_caps += 1;
    } else if (point == white){
        match.blacks_caps += 1;
    }else {
        UI::PrintLine("somthing's wrong");
    }

    for (int i = 0; i < comrades.size(); i++)
    {
        CaptureAllConnected(comrades[i], point);
    }
}
bool Game::CheckContiguousEmpty(Position pos, point first_contact=empty)
{
    bool controlled = true;
    if (!checked_board->GetElem(pos))
    {
        vector<point> adjacent = board->GetAllSurroundingElem(pos);
        //point first_contact = empty;
        
        for (auto contact : adjacent)
        {
            if (contact != empty){
                if (first_contact == empty)
                {
                    first_contact = contact;
                    controlling_player = first_contact;
                } else if (first_contact != contact) {
                    //try returning controlling player instead of controlled bool to move controlling player out of class scope
                    controlling_player = empty;
                    controlled = false;
                }
            }
        }
        checked_board->PlaceElem(pos, true);
        control_counter += 1;
        vector<Position> empties = board->GetPosForSurrElems(pos, empty);
        for (int i = 0; i < empties.size(); i++)
        {
            controlled = CheckContiguousEmpty(empties[i], first_contact);
        }
        return controlled;
    } else {
        return controlled;
    }
   
}

void Game::ProcessAction(Position pos)
{
    //process the consequences of the players turn
    point enemy = static_cast<point>(match.active_player * -1);
    vector<Position> enemies = board->GetPosForSurrElems(pos, enemy);
    for (size_t i = 0 ; i < enemies.size(); i++)
    {
        if(board->GetElem(enemies[i]) == enemy){
            if(CheckCapture(enemies[i], enemy)){
                CaptureAllConnected(enemies[i], enemy);
            }
        }
    }
    int score;
    if (match.active_player == black){
        score = match.blacks_caps;
    } else if(match.active_player == white){
        score = match.whites_caps;
    }
    UI::PrintPlayersScore(score, match.active_player);
}
void Game::CalculateScore()
{   //calculate final score
    int white_score = match.whites_caps + start_bias;
    int black_score = match.blacks_caps;

    checked_board->Clear();
    //check empty spaces    
    vector<Position> empty_spaces = board->GetAllPosForElem(empty);
    for(size_t i = 0; i < empty_spaces.size(); i++)
    {
        control_counter = 0;
        if (!checked_board->GetElem(empty_spaces[i])){
            //check if space controlled 
            if(CheckContiguousEmpty(empty_spaces[i])){
                if (controlling_player == white){
                    white_score += control_counter;
                } else if (controlling_player == black){
                    black_score += control_counter;
                }
            }
        }
    }
    UI::PrintFinalScores(black_score, white_score);
}
bool Game::CalculateTerritory(Position) 
{
    //check all connected empty spaces
}
