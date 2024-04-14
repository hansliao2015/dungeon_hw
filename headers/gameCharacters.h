#pragma once

#include "object.h"
#include "rooms.h"
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
class Antidote;
class Poison;
class Player;

class GameCharacter: public Object {
protected:
    int money;
    int maxHp;
    int currentHp;
    int atk;
    int def;
public:
    GameCharacter(string name, int _money, int mH, int a, int d);
    GameCharacter(string name, string tag, int _money, int mH, int a, int d);
    int getMoney() const;
    int getMaxHp() const;
    int getCurrentHp() const;
    int getAtk() const;
    int getDef() const;
    void setMoney(int);
    void takeDamage(int);
    bool checkIsDead() const;
    virtual void triggerEvent(GameCharacter* gameCharacter) = 0;
};


/*---------player------------*/

class Player: public GameCharacter {
private:
    int fullness;
    int moisture;
    int vitality;
    Room *currentRoom;
    Room *previousRoom;
    vector<Item*> backpack;
    Item *equippedItem;
    Poison *infectedPoison;
    bool isRetreat;
public:
    Player(string _name, int _maxHp, int _atk, int _def, int _Fullness, int _Moisture, int _Vitality, int _money);
    Room* getCurrentRoom() const;
    Room* getPreviousRoom() const;
    void addItem(Item*);
    void changeRoom(Room *);
    void retreat();
    void equip(Equipment*);
    void eat(Food*);
    void useAntidote(Antidote*);
    void briefState();
    void detailedState();
    void setCurrentRoom(Room*);
    void setPreviousRoom(Room*);
    void setInfectedPoison(Poison*);
    void updateTransitionState();
    void launchBattle(GameCharacter* enemy);
    void triggerEvent(GameCharacter* gameCharacter) override;
    void updateEnvironmentDamage(int fullnessDamage, int moistureDamage, int vitalityDamage);
    void openBackpack();
};

/*---------monster------------*/

class Monster: public GameCharacter {
private:
    Item *dropItem;
public:
    Monster(string _name, int _money, int _maxHp, int _atk, int _def);
    Item* getDropItem() const;
    void triggerEvent(GameCharacter* gameCharacter) override;
};

class Npc: public GameCharacter {
private:
    int index;
    string line;
    vector<Item*> items;
public:
    Npc(int index, string line, string _name, int _money, int _maxHp, int _atk, int _def);
    void triggerEvent(GameCharacter* gameCharacter) override;
    void addItem(Item *item);
    void speak();
    void trade(GameCharacter*);
};