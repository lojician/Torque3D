#include "Game.hpp"

#include <vector>
using std::vector;

Game::Game()
{
    board = new Board<point>(board_size);
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
    Board<bool> checked_board(board_size);
    SurroundingPositions sur_pos;
    point sur_points[4];
    if(!(pos.y == 0)){
        sur_pos.above += pos;
        sur_points[0]= board->PointCheck(sur_pos.above); 
    } else if(!(pos.y == (board_size -1))){
        sur_pos.below += pos;
        sur_points[1] = board->PointCheck(sur_pos.below);
    }
    if(!(pos.x == 0)){
        sur_pos.left+= pos;
        sur_points[2] = board->PointCheck(sur_pos.left);
    } else if(!(pos.x == (board_size -1))){
        sur_pos.right += pos;
        sur_points[3] = board->PointCheck(sur_pos.right);
    }
    for(auto& x: sur_points){
        
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