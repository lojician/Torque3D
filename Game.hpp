#include "Board.hpp"
class Game
{     
private:
    /* data */
    Board *board;
    int board_size = 0;
    point turn = empty;
    point player1 = black;
    point player2 = white;
public:
    gameStatus game_status = unstarted;
    Game();
    ~Game();
    void Game::Start();
    void Game::Play();
    void Game::Turn();
    void Game::CalculateScore();
    void Game::End();
};