#include "Game.hpp"
Game::Game()
{
    board = new Board(board_size);
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
        cout << "It is blacks turn to act. \n";
    } else if (active_player == black)
    {
        active_player = white;
        cout << "It is whites turn to act. \n";
    } else if (active_player == white)
    {
        active_player = black;
        cout << "It is blacks turn to act. \n";
    }
}
void Game::PlayerAction()
{
    bool valid = false;
    Position pos;
    //run until valid input is entered
    bool play = Input::PassOrPlay();
    if (play)
    {
        pos = Input::GetPosition(board_size);
        while(!valid){
            valid = board->PlacePiece(pos, active_player);
            if (!valid){
                cout << "The piece cannot be placed in that location\n";
                pos = Input::GetPosition(board_size);
            }
        }
        
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