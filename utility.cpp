#include "utility.h"
//Aliases for common functions
void clearBuffer(){
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
}
void printLine(string out){
    cout << out << endl;
}