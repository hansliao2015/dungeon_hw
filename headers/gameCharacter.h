#pragma once

#include "object.h"

#include <iostream>
#include <string>
using namespace std;

class GameCharacter: public Object {
private:
    int maxHp;
    int currentHp;
    int atk;
    int def;
public:
    GameCharacter(string, int, int, int);
    int getMaxHp() const;
    int getCurrentHp() const;
    int getAtk() const;
    int getDef() const;
    void takeDamage(int);
    bool checkIsDead() const;
};