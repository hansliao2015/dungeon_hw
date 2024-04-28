#pragma once

#include "object.h"
#include "gameCharacters.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Player;

class Room {
private:
    int index;
    Room *upRoom;
    Room *downRoom;
    Room *leftRoom;
    Room *rightRoom;
    bool isExit;
    vector<Object *> objects;
    bool handlePlayerMovements(Player *player);
public:
    Room(int);

    string tag;
    // 7 getter
    Room *getUpRoom() const;
    Room *getDownRoom() const;
    Room *getLeftRoom() const;
    Room *getRightRoom() const;
    bool getIsExit() const;
    int getIndex() const;
    vector<Object *> getObjects() const;

    // 6 setter
    void setUpRoom(Room *);
    void setDownRoom(Room *);
    void setLeftRoom(Room *);
    void setRightRoom(Room *);
    void setIsExit(bool);
    void setIndex(int);

    // other functions
    void addObject(Object *);
    virtual void roomAction(Player *player);
    bool canPass();
    bool encounterObjects(Player *player);
    virtual void drawRoomAndPlayerState(Player *player);
    bool showPlayerOptions(Player *player);
};

class Desert: public Room {
public:
    Desert(int);
    void roomAction(Player *player) override;
};

class Forest: public Room {
public:
    Forest(int);
    void roomAction(Player *player) override;
};

class Swamp: public Room {
public:
    Swamp(int);
    void roomAction(Player *player) override;
};