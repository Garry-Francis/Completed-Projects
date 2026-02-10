/*-------------------------------------------------------------------------------------
* Name: Garry Francis
* Project: FightSim
*
* This is the header file for the Character class. It contains the declarations for the
* character class, the constructor, and the class functions.
*------------------------------------------------------------------------------------*/

#ifndef PROJECT2_FIGHTSIM_TEMPLATE_CHARACTER_H
#define PROJECT2_FIGHTSIM_TEMPLATE_CHARACTER_H
#include <string>

// declaration of the class
class Character {
private:
    std::string name;
    std::string role;
    int hitPoints{0};
    int attackBonus{0};
    int bonusDamage{0};
    int armorClass{0};

public:

    // declaration of the constructor
    Character(std::string name,
              std::string role,
              int hitPoints,
              int attackBonus,
              int bonusDamage,
              int armorClass);

    // declarations of the class functions
    void print(std::ostream& os) const;
    void attack(Character& otherCharacter) const;
    void damage(int damageDone);
    int getHealth() const;
    std::string getName() const;
    std::string getRole() const;
    std::string getNameTheRole() const;

};


#endif //PROJECT2_FIGHTSIM_TEMPLATE_CHARACTER_H