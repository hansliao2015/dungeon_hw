#include "../headers/room.h"

Room::Room() {
    this->upRoom = nullptr;
    this->downRoom = nullptr;
    this->leftRoom = nullptr;
    this->rightRoom = nullptr;
    this->isExit = false;
    this->index = -1;
}

Room::Room(bool isExit, int index, vector<Object *> objects) {
    this->upRoom = nullptr;
    this->downRoom = nullptr;
    this->leftRoom = nullptr;
    this->rightRoom = nullptr;
    this->isExit = isExit;
    this->index = index;
    this->objects = objects;
}

// getter: 7 functions

Room *Room::getUpRoom() const {
    return this->upRoom;
}

Room *Room::getDownRoom() const {
    return this->downRoom;
}

Room *Room::getLeftRoom() const {
    return this->leftRoom;
}

Room *Room::getRightRoom() const {
    return this->rightRoom;
}

bool Room::getIsExit() const {
    return this->isExit;
}

int Room::getIndex() const {
    return this->index;
}

vector<Object *> Room::getObjects() const {
    return this->objects;
}

//setter: 6 functions

void Room::setUpRoom(Room *upRoom) {
    this->upRoom = upRoom;
}

void Room::setDownRoom(Room *downRoom) {
    this->downRoom = downRoom;
}

void Room::setLeftRoom(Room *leftRoom) {
    this->leftRoom = leftRoom;
}

void Room::setRightRoom(Room *rightRoom) {
    this->rightRoom = rightRoom;
}

void Room::setIsExit(bool isExit) {
    this->isExit = isExit;
}

void Room::setIndex(int index) {
    this->index = index;
}

// other functions

void Room::addObject(Object *object) {
    this->objects.push_back(object);
}

void Room::clearObject(Object *object) {
    for (int i = 0; i < this->objects.size(); i++) {
        if (this->objects[i] == object) {
            this->objects.erase(this->objects.begin() + i);
            break;
        }
    }
}

