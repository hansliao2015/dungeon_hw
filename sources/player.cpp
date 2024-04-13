#include "../headers/player.h"


Player::Player(string name, int mH, int a, int d): GameCharacter(name, mH, a, d), currentRoom(nullptr), previousRoom(nullptr) {}

void Player::updateState() {
    // update player's states when adding/removing items and changing rooms
}

void Player::addItem(Item *item) {
    backpack.push_back(item);
    updateState();
}

void Player::changeRoom(Room *room) {
    previousRoom = currentRoom;
    currentRoom = room;
    updateState();
}

void Player::retreat() {
    Room *temp = currentRoom;
    currentRoom = previousRoom;
    previousRoom = temp;
    updateState();
}