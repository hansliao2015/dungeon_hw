#include "../headers/gameCharacters.h"


Player::Player(string _name, int _maxHp, int _atk, int _def, int _Fullness, int _Moisture, int _Vitality, int _money): GameCharacter(_name, _maxHp, _atk, _def), fullness(_Fullness), moisture(_Moisture), vitality(_Vitality), money(_money) {
    currentRoom = nullptr;
    previousRoom = nullptr;
    equippedItem = nullptr;
}

void Player::addItem(Item *item) {
    backpack.push_back(item);
}

void Player::changeRoom(Room *room) {
    previousRoom = currentRoom;
    currentRoom = room;
}

void Player::retreat() {
    Room *temp = currentRoom;
    currentRoom = previousRoom;
    previousRoom = temp;
}

void Player::briefState() {
    cout << "Player: " << getName() << endl;
    cout << "HP: " << getCurrentHp() << "/" << getMaxHp() << endl;
    cout << "ATK: " << getAtk() << endl;
    cout << "DEF: " << getDef() << endl;
    cout << "Equipped item: " << equippedItem->getName() << endl;
}

void Player::equip(Equipment *equipment) {
    equippedItem = equipment;
    briefState();
}

void Player::setCurrentRoom(Room *room) { currentRoom = room; }

void Player::setPreviousRoom(Room *room) { previousRoom = room; }

void Player::setInfectedPoison(Poison *poison) { infectedPoison = poison; }

void Player::updateDamage() {
    if (infectedPoison) {
        if (infectedPoison->getDuration() == 0) {
            infectedPoison = nullptr;
            return;
        }
        currentHp -= infectedPoison->getDamage();
        infectedPoison->decreaseDuration();
    }
}

void Player::eat(Food *food) {
    currentHp += food->getAddHp();
    if (currentHp > maxHp) currentHp = maxHp;
    fullness += food->getAddFullness();
    moisture += food->getAddMoisture();
    vitality += food->getAddVitality();
}