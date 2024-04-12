#include "../headers/room.h"

Room::Room(int _index): index(_index), upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr), isExit(false), objects() {}

// getter: 7 functions
Room *Room::getUpRoom() const { return this->upRoom; }
Room *Room::getDownRoom() const { return this->downRoom; }
Room *Room::getLeftRoom() const { return this->leftRoom; }
Room *Room::getRightRoom() const { return this->rightRoom; }
bool Room::getIsExit() const { return this->isExit; }
int Room::getIndex() const { return this->index; }
vector<Object *> Room::getObjects() const { return this->objects; }

//setter: 6 functions
void Room::setUpRoom(Room *upRoom) { this->upRoom = upRoom; }
void Room::setDownRoom(Room *downRoom) { this->downRoom = downRoom; }
void Room::setLeftRoom(Room *leftRoom) { this->leftRoom = leftRoom; }
void Room::setRightRoom(Room *rightRoom) { this->rightRoom = rightRoom; }
void Room::setIsExit(bool isExit) { this->isExit = isExit; }
void Room::setIndex(int index) { this->index = index; }

// other functions

void Room::addObject(Object *object) {
    this->objects.push_back(object);
}



void Room::roomAction(Player *player) {
    cout << "你來到了一個普通的房間，在這裡你不會遇到任何東西，可以安心地調整狀態，休息過後再出發。";
}
