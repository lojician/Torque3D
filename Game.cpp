#include "Game.hpp"
Game::Game(){
    board = new Board(board_size);
}
Game::~Game(){
    delete board;
}
void Game::Start(){
    game_status = started;
}
void Game::End(){
    game_status = unstarted;
}
void Game::CalculateScore(){

}
void Game::Turn(){

}