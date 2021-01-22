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
    //place piece where player specified
}
void Game::ProcessTurn(){
    
}
void Game::CalculateScore(){

}
void Game::End(){
    game_status = unstarted;
}