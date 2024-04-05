#pragma once

#include "object.h"

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Room: public Object {
private:
    Room *upRoom;
    Room *downRoom;
    Room *leftRoom;
    Room *rightRoom;
    bool isExit;
    int index;
    vector<Object *> objects;
public:
    Room();
    Room(bool, int, vector<Object *>);

    Room *getUpRoom() const;
    Room *getDownRoom() const;
    Room *getLeftRoom() const;
    Room *getRightRoom() const;
    bool getIsExit() const;
    int getIndex() const;
    vector<Object *> getObjects() const;
    
    void setUpRoom(Room *);
    void setDownRoom(Room *);
    void setLeftRoom(Room *);
    void setRightRoom(Room *);
    void setIsExit(bool);
    void setIndex(int);

    void addObject(Object *);
    void clearObject(Object *);

};