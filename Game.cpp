#include "Game.hpp"
Game::Game(){
    board = new Board(board_size);
}
Game::~Game(){
    delete board;
}
void Game::Start(){
    game_status = started;
    Play();
}
void Game::Play(){
    while(game_status != 0){
        DetermineTurn();
        PlayerAction();
    }
}
void Game::DetermineTurn(){
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
void Game::PlayerAction(){
    //get player input
    std::string input; 
    bool valid = false;
    int x,y;
    std::cout << "Do you want to play(p), or skip(s)\n";    
    std::cin >> input;
    while(!valid)
        if (input == "s"){
            valid = true;
        }else if (input == "p")
        {
            std::cout << "enter the colunm and row number\n in the following format:1 2";
            //place piece where player specified
            std::cin >> x , y;
            std::cout << x;
            valid = true;
        } else {
            std::cout << "input invalid";
        }
    
    
}
void Game::ProcessTurn(){
    //process the consequences of the players turn
}
void Game::CalculateScore(){
    //calculate final score
}
void Game::End(){
    game_status = unstarted;
}