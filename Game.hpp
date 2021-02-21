#pragma once
#include "elements.hpp"
//Forward Declarations
template <typename T>
class Board;
class MatchInfo;
// TODO: Add ability to play different kinds of games
// TODO: Add menu
// TODO: Finish adding go rules
enum gameStatus {unstarted = 0, started = 1, ending = 2};
class Game
{     
private:
    /* data */
    MatchInfo match = MatchInfo();
    Board<point> *board;
    Board<bool> *checked_board;
    int start_bias;
    //move control variables out of class scope and back into local scopes
    int control_counter;
    point controlling_player;
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
    bool CheckContiguousEmpty(Position, point);
    void HandleOptions();
    void CalculateScore();
    bool CalculateTerritory(Position);
};