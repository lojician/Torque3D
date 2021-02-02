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
            if(pos == captured){
                valid = board->PlacePiece(pos, active_player);
            }
            if (!valid){
                cout << "The piece cannot be placed in that location" << endl;
                pos = IO::GetPosition(board_size);
            }
        }
        
    }
}
bool Game::CheckCapture(Position pos, point piece)
{

}
bool Game::CheckSurrounding(Position pos, point piece)
{
    
    SurroundingPositions sur_pos;
    point sur_points[4];
    int i = 0;
    if(!(pos.y == 0)){
        if (CheckOffset(pos, sur_pos.above, sur_points[i]))
        {
            i++;
        }
    } else if(!(pos.y == (board_size -1))){
        if (CheckOffset(pos, sur_pos.below, sur_points[i]))
        {
            i++;
        }
    }
    if(!(pos.x == 0)){
        if (CheckOffset(pos, sur_pos.left, sur_points[i]))
        {
            i++;
        }
    } else if(!(pos.x == (board_size -1))){
        if (CheckOffset(pos, sur_pos.right, sur_points[i]))
        {
            i++;
        }
    }
    for(auto& x: sur_points){
        
    }
}

bool Game::CheckOffset(Position pos, Position offset, point p){
    pos += offset;
    if(!(checked_board->PointCheck(pos)))
    {
        p = board->PointCheck(pos);
        return true;
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