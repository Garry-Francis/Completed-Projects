/*-----------------------------------------------------------------------------
* Name: Garry Francis
* Project: Simulating Dice Rolls
*
* This is a program that will take a user input integer and then roll 2 D6
* (random number 1-6) that many times and store each value (2-12) in an array.
* Then it will output each number and how many times it was "rolled".
*----------------------------------------------------------------------------*/

#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int main() {

    // Set the random seed to the current time
    srand(time(nullptr));

    // Initialize numRolls empty and arrRolledDice with all zeros
    int numRolls;
    int arrRolledDice[13] = {0};

    // Get the number of rolls from the user
    cout << "How many rolls?" << endl;
    cin >> numRolls;

    // Rolls the number of times said by the user and records the results
    // in their corresponding index on the array
    cout << "Simulating " << numRolls << " rolls..." << endl;
    for (int i = 0; i < numRolls; i++) {
        int rolledNum = rand() % 11 + 2;
        arrRolledDice[rolledNum] = arrRolledDice[rolledNum] + 1;
    }

    // Prints the contents of the array with the counted numbers rolled
    cout << "Results:" << endl;
    for (int i = 2; i < 13; i++) {
        cout << i << " was rolled " << arrRolledDice[i] << " times" << endl;
    }

    return 0;
}