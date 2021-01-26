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
    //get player input
    std::string input; 
    Position pos;
    bool valid = false;
    //run until valid input is entered
    while(!valid)
    {
        cout << "Do you want to play(p), or skip(s)\n";    
        cin >> input;
        cin.clear();
        if (input == "s"){
            valid = true;
        }else if (input == "p")
        {
            cout << "Enter the colunm and row number from 0 to " << (board_size - 1) << "\n";
            //place piece where player specified
            cin >> pos.x >> pos.y;
            cin.clear();
            if ((pos.x >= 0&& pos.x < board_size)&&(pos.y >= 0&& pos.y < board_size)){
                cout << pos.x << "\n";
                valid = board->PlacePiece(pos, active_player);
                if (!valid){
                    cout << "The piece cannot be placed in that location\n";
                }
            } else { 
                cout << "The location is outside the valid range\n";
            }
           
            
        } else {
            cout << "Invalid input: " << input << "\n";
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