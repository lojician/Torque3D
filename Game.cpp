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
                valid = board->PlacePiece(pos, active_player);
            }
            
            if (!valid){
                cout << "The piece cannot be placed in that location" << endl;
                pos = IO::GetPosition(board_size);
            }
        }
        
    }
}
bool Game::CheckSuicide(Position pos){
    if(CheckSurrounded(pos, active_player))
    {
        //holds the array size for *enemies
        size_t num_enemies;
        point enemy = static_cast<point>(active_player * -1);
        Position *enemies = board->GetPositionsForElem(pos, enemy, num_enemies);
        //check capture of surrounding enemies
        for (size_t i; i < num_enemies; i++)
        {
            CheckCapture(pos, active_player);
        }
    }
}
bool Game::CheckCapture(Position pos, point piece)
{
    //look for first empty space amongst connected friendlies

}



bool Game::CheckSurrounded(Position pos, point piece)
{
    
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