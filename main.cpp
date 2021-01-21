#include "Board.cpp"
#include "Game.cpp"
#include <iostream>

int main(){
    bool exit = false;
   
   
    
    while (!exit)
    {
        std::string  input;      
        std::cin >> input;
        Game game;
        if (input == "q"){
            exit = true;
        } else if ( input == "s"){
            game.Start();
            while(game.game_status != 0){
               
            }
        }
    }
 
}
