#include "Board.hpp"

class Game
{     
private:
    /* data */
    Board *board;
    int board_size = 9;
    point active_player = empty;
public:
    gameStatus game_status = unstarted;
    Game();
    ~Game();
    void Start();
    void Play();
    void DetermineTurn();
    void PlayerAction();
    char GetInput();
    void ProcessTurn(Position);
    bool CheckCapture(Position, point);
    void CalculateScore();
    void End();
};