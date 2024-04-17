#pragma once

#include "gameCharacters.h"
#include "rooms.h"
#include "items.h"

#include <iostream>
#include <string>
using namespace std;

class Dungeon {
private:
    Room *room;
    vector<Room *> rooms;
    vector<Poison *> poisons;
    vector<Equipment *> equipments;
    vector<Food *> foods;
    vector<Antidote *> antidotes;
    vector<Monster *> monsters;
    vector<Npc *> npcs;
    void initEquipments();
    void initFoods();
    void initAntidotes();
    void initPlayer();
    void initNpcs();
    void initMonsters();
    void initRooms();
public:
    Dungeon();
    Player* player;
    bool isPlayerChangeRoom;
    bool isGameOver();
    bool isPlayerWin();
    bool isPlayerLose();
    void init();
    void handleMovement();
    void showOption();
    void printResult();
    void runGame();
    void drawGameConsole();
};