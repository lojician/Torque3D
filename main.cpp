#include "Game.hpp"
#include "UI.hpp"
int main(){
    bool exit = false;
   
   
    
    while (!exit)
    {
        char input = UI::StartEntry();
        Game game;
        if (input == 'q'){
            exit = true;
        } else if ( input == 's'){
            game.Start();
        }
    }
 
}
