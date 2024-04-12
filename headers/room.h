#pragma once

#include "object.h"
#include "player.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Player;

class Room: public Object {
private:
    int index;
    Room *upRoom;
    Room *downRoom;
    Room *leftRoom;
    Room *rightRoom;
    bool isExit;
    vector<Object *> objects;
public:
    Room(int);

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

};