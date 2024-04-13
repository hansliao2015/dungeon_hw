#pragma once

#include "object.h"
#include "gameCharacters.h"

#include <iostream>
#include <string>
using namespace std;

class Player;

class Item: public Object {
private:
    int money;
    int addHp;
    int addAtk;
    int addDef;
    int addFullness;
    int addMoisture;
    int addVitality;
public:
    Item(string, int, int, int, int, int, int, int);
    virtual void use(Player*) = 0;
    int getMoney() const;
    int getAddHp() const;
    int getAddAtk() const;
    int getAddDef() const;
    int getAddFullness() const;
    int getAddMoisture() const;
    int getAddVitality() const;
};

class Food: public Item {
public:
    Food(string, int, int, int, int, int);
    void use(Player*) override;
};

class Equipment: public Item {
public:
    Equipment(string, int, int, int, int, int, int, int);
    void use(Player*) override;
};

class Antidote: public Item {
public:
    Antidote(string, int, int, int, int, int, int, int);
    void use(Player*) override;
};