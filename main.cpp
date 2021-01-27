#include "Game.hpp"

int main(){
    bool exit = false;
   
   
    
    while (!exit)
    {
        char input = IO::StartEntry();
        Game game;
        if (input == 'q'){
            exit = true;
        } else if ( input == 's'){
            game.Start();
        }
    }
 
}
