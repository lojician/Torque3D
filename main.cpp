#include "Game.hpp"

int main(){
    bool exit = false;
   
   
    
    while (!exit)
    {
        std::string  input;  
        cout << "q to quit, s to start\n";
        cin >> input;
        Game game;
        if (input == "q"){
            exit = true;
        } else if ( input == "s"){
            game.Start();
        }
    }
 
}
