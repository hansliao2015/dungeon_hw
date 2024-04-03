#pragma once

#include "object.h"

#include <iostream>
#include <string>
using namespace std;

class Item: public Object {
private:
    int addHealth;
    int addAttack;
    int addDefense;
public:
    Item();
    Item(string, int, int, int);
    int getAddHealth() const;
    int getAddAttack() const;
    int getAddDefense() const;
    void setAddHealth(int aH);
    void setAddAttack(int aA);
    void setAddDefense(int aD);
};