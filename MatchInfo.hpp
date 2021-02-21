#include "utility.hpp"
#include "elements.hpp"

class MatchInfo{
private:

public:
int board_size;
point active_player;
int whites_caps, blacks_caps;
bool passed_last_turn;
Position captured;
char delim = ',';
void LoadSaveFile(string state_info);
string GetSaveString();


};