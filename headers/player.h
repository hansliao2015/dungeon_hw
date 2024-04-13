#pragma once

#include "gameCharacter.h"
#include "room.h"
#include "items.h"
#include "poison.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class GameCharacter;
class Room;
class Item;
class Equipment;
class Food;
class Poison;

class Player: public GameCharacter {
private:
    int hp;
    int maxHp;
    int atk;
    int def;
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