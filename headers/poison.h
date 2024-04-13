#pragma once

#include <string>
#include <iostream> 
using namespace std;

#include "gameCharacters.h"

class Player;

class Poison {
private:
    string name;
    int damage;
    int maxDuration;
    int duration;
public:
    Poison(string _name, int _damage, int _maxDuration);
    int getDamage();
    int getDuration();
    void decreaseDuration();
    void infect(Player* player);
};