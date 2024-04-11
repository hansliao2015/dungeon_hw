#pragma once

#include "player.h"
#include "room.h"

#include <iostream>
#include <string>
using namespace std;

class Dungeon {
private:
    Player player;
    Room *room;
public:
    Dungeon();
    void createMap();
    void handleMovement();
    void chooseAction();
    void getPlayer();
    void getRoom();
    void setPlayer(Player player);
    void setRoom(Room *room);
};