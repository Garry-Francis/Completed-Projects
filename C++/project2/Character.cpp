/*-------------------------------------------------------------------------------------
* Name: Garry Francis
* Project: FightSim
*
* This is the cpp file for the Character class. It contains the constructor and all
* the function definitions. This file includes: the Character constructor, The print
* function, the attack function, the damage function. the getHealth function, the
* getName function, and the getRole function.
*------------------------------------------------------------------------------------*/

#include "Character.h"
#include <cstdlib>
#include <iostream>

using namespace std;

// Constructor for Character.
Character::Character(std::string name,
    std::string role,
    int hitPoints,
    int attackBonus,
    int bonusDamage,
    int armorClass)
: name(std::move(name)),
  role(std::move(role)),
  hitPoints(hitPoints),
  attackBonus(attackBonus),
  bonusDamage(bonusDamage),
  armorClass(armorClass)
{
}

// Print function: Prints a summary of the created character
void Character::print(std::ostream& os) const {
    os << "Character Summary" << endl;
    os << "-----------------" << endl;
    os << getName() << " the " << getRole() << endl;
    os << "HP: " << getHealth() << endl;
    os << "AB: " << this->attackBonus << endl;
    os << "DB: " << this->bonusDamage << endl;
    os << "AC: " << this->armorClass << endl << endl;
}

// Attack function: Rolls for hit and calculates damage.
void Character::attack(Character& otherCharacter) const {
    cout << getName() << " attacks!" << endl;
    int hitRoll = rand() % 20 + 1;
    int totalHit = hitRoll + this->attackBonus;
    cout << "Attack roll: " << hitRoll << " + " << this->attackBonus << " = " << totalHit << " --> ";
    // Hit check
    if (totalHit >= otherCharacter.armorClass) {
        cout << "HIT!" << endl;
        int damageRoll = rand() % 10 + 1;
        int damageDone = damageRoll + this->bonusDamage;
        cout << "Damage: " << damageRoll << " + " << this->bonusDamage << " = " << damageDone << endl;
        otherCharacter.damage(damageDone);
    }
    else {
        cout << "MISS!" << endl << endl;
    }
}

// Damage function: Subtracts damage from Character hit points. Sets to 0 if it goes below.
void Character::damage(int damageDone) {
    this->hitPoints -= damageDone;
    if (this->hitPoints < 0) {
        this->hitPoints = 0;
    }
    cout << getName() << " has " << getHealth() << " hit points remaining." << endl << endl;
}

// Returns the Character's health
int Character::getHealth() const {
    return hitPoints;
}

// Returns the Character's name
std::string Character::getName() const {
    return name;
}

// Returns the Character's role
std::string Character::getRole() const {
    return role;
}