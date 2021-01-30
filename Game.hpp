#pragma once
#include "Board.hpp"
#include "Input.hpp"
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
    void ProcessTurn(Position);
    bool CheckCapture(Position, point);
    bool CheckSurrounding(Position, point);
    void CalculateScore();
    void End();
};