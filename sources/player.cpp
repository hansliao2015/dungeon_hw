#include "../headers/player.h"

Player::Player(): GameCharacter(), currentRoom(nullptr), previousRoom(nullptr) {}

Player::Player(string name, int mH, int a, int d): GameCharacter(name, mH, a, d), currentRoom(nullptr), previousRoom(nullptr) {}

void Player::updateStates() {
    // update player's states when adding/removing items and changing rooms
}

void Player::addItem(Item item) {
    inventory.push_back(item);
    updateStates();
}

void Player::changeRoom(Room *room) {
    previousRoom = currentRoom;
    currentRoom = room;
    updateStates();
}