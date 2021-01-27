#include "utility.h"
//Aliases for common functions
//using string = std::string;
void clearBuffer(){
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}
void printLine(string out){
    cout << out << endl;
}