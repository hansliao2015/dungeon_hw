#pragma once

#include "object.h"
#include "room.h"
#include "items.h"
#include "poison.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Room;
class Item;
class Equipment;
class Food;
class Poison;

class GameCharacter: public Object {
protected:
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


/*---------player------------*/

class Player: public GameCharacter {
private:
    int fullness;
    int moisture;
    int vitality;
    int money;
    Room *currentRoom;
    Room *previousRoom;
    vector<Item*> backpack;
    Item *equippedItem;
    Poison *infectedPoison;
public:
    Player(string _name, int _maxHp, int _atk, int _def, int _Fullness, int _Moisture, int _Vitality, int _money);
    void addItem(Item*);
    void changeRoom(Room *);
    void retreat();
    void equip(Equipment*);
    void briefState();
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInfectedPoison(Poison*);
    void updateDamage();
    void eat(Food*);
    // getter

    // setter
};