#include "Game.hpp"
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
            valid = board->PlacePiece(pos, active_player);
            if (!valid){
                cout << "The piece cannot be placed in that location" << endl;
                pos = IO::GetPosition(board_size);
            }
        }
        
    }
}
bool Game::CheckCapture(Position pos, point piece){

}
bool Game::CheckSurrounding(Position pos, point piece){
    SurroundingPoints sur_points;
    if(!(pos.y == 0)){
        Position above = pos;
        above.y -= 1;
        sur_points.above = board->PointCheck(above);
    } else if(!(pos.y == (board_size -1))){
        Position below = pos;
        below.y += 1;
        sur_points.below = board->PointCheck(below);
    }
    if(!(pos.x == 0)){
        Position left = pos;
        left.x -= 1;
        sur_points.left = board->PointCheck(left);
    } else if(!(pos.x == (board_size -1))){
        Position right = pos;
        right.x += 1;
        sur_points.right = board->PointCheck(right);
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