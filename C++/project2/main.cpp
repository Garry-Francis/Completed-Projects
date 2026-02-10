/*-------------------------------------------------------------------------------------
* Name: Garry Francis
* Project: FightSim
*
* This is a program that will take a user input to create two "Characters".
* Two strings and four ints will be passed into a Character class constructor as:
*
* String name: The name of the character
* String role: What the character is (wizard, fighter, etc.)
* int hitPoints: Amount of damage character can take before defeat
* int attackBonus: Added to rolls made to hit the opponent
* int bonusDamage: Added to damage rolls made after a hit
* int armorClass: Number that the hit roll needs to be >= to hit
*
* After two characters are constructed, a loop will begin where they take turns
* attacking each other (by rolling 1-20 + attackBonus). If they hit a damage roll
* (1-10 + bonusDamage) is made and the result is removed from the opponents hit points.
* This will continue until one of the characters reaches 0 hit points, which will
* cause a winner to be declared, the loop to break, and the program to end.
*------------------------------------------------------------------------------------*/

#include "Character.h"
#include <iostream>
#include <ctime>
#include <limits>

using namespace std;

int main() {

    // Random seeding for the rolls made in attack and damage functions
    srand(time(nullptr));

    // Declaration of constructor variables
    string name;
    string role;
    int hitPoints;
    int attackBonus;
    int bonusDamage;
    int armorClass;

    // Prompts user for and collects information for the first Character
    cout << "First characters name?" << endl;
    getline(cin, name);
    cout << name << "'s role?" << endl;
    getline(cin, role);
    cout << name << " the " << role << "'s hit points?" << endl;
    cin >> hitPoints;
    cout << name << " the " << role << "'s attack bonus?" << endl;
    cin >> attackBonus;
    cout << name << " the " << role << "'s damage bonus?" << endl;
    cin >> bonusDamage;
    cout << name << " the " << role << "'s armor class?" << endl;
    cin >> armorClass;

    // Gives entered information to constructor and creates the first Character
    Character c1(name, role, hitPoints, attackBonus, bonusDamage, armorClass);

    // Prints a summary of the first Character
    c1.print(cout);

    // Clears the leftover newline from cin for the next getLine()
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Prompts user for and collects information for the second Character
    cout << "Second characters name?" << endl;
    getline(cin, name);
    cout << name << "'s role?" << endl;
    getline(cin, role);
    cout << name << " the " << role << "'s hit points?" << endl;
    cin >> hitPoints;
    cout << name << " the " << role << "'s attack bonus?" << endl;
    cin >> attackBonus;
    cout << name << " the " << role << "'s damage bonus?" << endl;
    cin >> bonusDamage;
    cout << name << " the " << role << "'s armor class?" << endl;
    cin >> armorClass;

    // Gives entered information to constructor and creates the second Character
    Character c2(name, role, hitPoints, attackBonus, bonusDamage, armorClass);

    // Prints a summary of the second Character
    c2.print(cout);

    // Beginning of the combat loop
    cout << "Simulated Combat:" << endl << endl;

    // Continue while both characters have more than 0 hitPoints
    while (c1.getHealth() > 0 && c2.getHealth() > 0) {
        // The first character attacks the second character
        c1.attack(c2);
        // If the second character has 0 hit points, the first character wins
        if (c2.getHealth() == 0) {
            cout << c1.getName() << " wins!";
            break;
        }
        // The second character attacks the first character
        c2.attack(c1);
        // If the first character has 0 hit points, the second character wins
        if (c1.getHealth() == 0) {
            cout << c2.getName() << " wins!";
            break;
        }
    }
    return 0;
}