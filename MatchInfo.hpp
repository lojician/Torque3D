#include "utility.hpp"
#include "elements.hpp"

template <typename T>
class Board;
class MatchInfo{
private:

public:
Board<point> *board;
int board_size;
point active_player;
int whites_caps, blacks_caps;
bool passed_last_turn;
Position captured;
char delim = ',';

MatchInfo(int = 9);
~MatchInfo();
string GetSaveString();
void LoadSaveFile(string state_info);
void SaveGame();
void LoadGame();
};