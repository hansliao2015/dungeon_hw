#pragma once

#include "gameCharacter.h"
#include "room.h"
#include "item.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Room;

class Player: public GameCharacter {
private:
    Room *currentRoom;
    Room *previousRoom;
    vector<Item> backpack;
    void updateState();
public:
    Player();
    Player(string, int, int, int);
    void addItem(Item);
    void changeRoom(Room *);
    void retreat();
    // getter

    // setter
};