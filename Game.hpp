#pragma once
#include "elements.hpp"
//Forward Declarations
template <typename T>
class Board;

// TODO: Add ability to play different kinds of games
// TODO: Add menu
// TODO: Finish adding go rules
enum gameStatus {unstarted = 0, started = 1, player_acting = 2, processing_action = 3};
class Game
{     
private:
    /* data */
    Board<point> *board;
    int board_size;
    point active_player;
    Position captured;
    Board<bool> *checked_board;
    int whites_caps, blacks_caps;
public:
    gameStatus game_status;
    Game();
    ~Game();
    void Start();
    void Play();
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
    void End();
};