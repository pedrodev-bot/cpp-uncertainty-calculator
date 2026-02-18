#include "calculator.hpp"
#include "ui.hpp"
#include <iomanip>
#include <iostream>
#include <windows.h>

using namespace std;

int main(){
    // Ensures that the terminal will accept textual accents.
    SetConsoleOutputCP(65001);

    // Function that asks the user what value he wants to calculate.
    getFunction();

    // End the program.
    cout << "\nThe program has been stopped.\n";
    return 0;
}