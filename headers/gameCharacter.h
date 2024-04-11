#pragma once

#include "object.h"

#include <iostream>
#include <string>
using namespace std;

class GameCharacter: public Object {
private:
    int maxHealth;
    int currentHp;
    int atk;
    int def;
public:
    GameCharacter();
    GameCharacter(string, int, int, int);
    int getMaxHp() const;
    int getCurrentHp() const;
    int getAtk() const;
    int getDef() const;
    void updateState(int, int, int);
    bool checkIsDead() const;
    void takeDamage(int);
};