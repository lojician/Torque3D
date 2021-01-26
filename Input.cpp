#include "Input.hpp"

bool Input::PassOrPlay(){
    char input; 
    while (true){
        cout << "Do you want to play(p), or skip(s)\n";    
        cin >> input;
        clearBuffer();
        if (input == 'p'){
            return true;
        } else if (input == 's')
        {
            return false;
        }
        else {
            cout << "Invalid input: " << input << "\n";
            cin.clear();
        }
    }
}
