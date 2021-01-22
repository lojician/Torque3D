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
        
    }
}
void Game::Turn(){

}
void Game::CalculateScore(){

}
void Game::End(){
    game_status = unstarted;
}