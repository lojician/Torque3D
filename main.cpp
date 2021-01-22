#include "Board.cpp"
#include "Game.cpp"


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
        }
    }
 
}
