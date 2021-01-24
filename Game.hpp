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
    void Start();
    void Play();
    void DetermineTurn();
    void PlayerAction();
    void ProcessTurn(Position);
    void CalculateScore();
    void End();
};