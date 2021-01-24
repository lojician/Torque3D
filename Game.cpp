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
    } else if (active_player == black)
    {
        active_player = white;
    } else if (active_player == white)
    {
        active_player = black;
    }
}
void Game::PlayerAction()
{
    valid = false;
    //get player input
    std::string input; 
    //bool valid = false;
    Position pos;
    while(!valid)
    {
        cout << "Do you want to play(p), or skip(s)\n";    
        cin >> input;
        if (input == "s"){
            valid = true;
        }else if (input == "p")
        {
            cout << "enter the colunm and row number\n";
            //place piece where player specified
            cin >> pos.x >> pos.y;
            cout << pos.x << "\n";
            valid = board->PlacePiece(pos, active_player);
            cout << "Entry is " << valid << "\n";
            
        } else {
            cout << "Invalid input\n";
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