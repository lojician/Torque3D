#pragma once
#include "elements.hpp"
//Forward Declarations
template <typename T>
class Board;

// TODO: Add ability to play different kinds of games
// TODO: Add menu
// TODO: Finish adding go rules
enum gameStatus {unstarted = 0, started = 1, ending = 2};
class Game
{     
private:
    /* data */
    Board<point> *board;
    int board_size;
    point active_player;
    Position captured;
    Board<bool> *checked_board;
    int start_bias;
    int whites_caps, blacks_caps;
    bool passed_last_turn;
public:
    gameStatus game_status;
    Game();
    ~Game();
    void Start();
    void Play();
    void End();
    void DetermineTurn();
    void PlayerAction();
    void ProcessAction(Position);
    bool CheckCapture(Position, point);
    bool CheckSuicide(Position);
    bool CheckSurrounded(Position,point);
    bool CheckAllXForY(Position, point, point);
    void CaptureAllConnected(Position, point);
    void HandleOptions();
    void CalculateScore();
    bool CheckControl(Position);
};