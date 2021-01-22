#include "Board.hpp"
class Game
{     
private:
    /* data */
    Board *board;
    int board_size = 0;
    point active_player = empty;
public:
    gameStatus game_status = unstarted;
    Game();
    ~Game();
    void Game::Start();
    void Game::Play();
    void Game::DetermineTurn();
    void Game::PlayerAction();
    void Game::ProcessTurn();
    void Game::CalculateScore();
    void Game::End();
};