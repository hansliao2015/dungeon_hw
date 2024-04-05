#pragma once

#include "gameCharacter.h"
#include "room.h"
#include "item.h"

#include <iostream>
#include <string>
using namespace std;

class Player: public GameCharacter {
private:
    Room *currentRoom;
    Room *previousRoom;
    vector<Item> inventory;
    void updateStates();
public:
    Player();
    Player(string, int, int, int);
    void addItem(Item);
    void changeRoom(Room *);
    // getter

    // setter
};