#pragma once

#include "object.h"

#include <iostream>
#include <string>
using namespace std;

class GameCharacter: public Object {
private:
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
public:
    GameCharacter();
    GameCharacter(string, int, int, int);
    int getMaxHealth() const;
    int getCurrentHealth() const;
    int getAttack() const;
    int getDefense() const;
    void setMaxHealth(int);
    void setCurrentHealth(int);
    void setAttack(int);
    void setDefense(int);
    bool checkIsDead() const;
    void takeDamage(int);
};