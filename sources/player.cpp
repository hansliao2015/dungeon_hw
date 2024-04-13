#include "../headers/gameCharacters.h"

Player::Player(string _name, int _maxHp, int _atk, int _def, int _Fullness, int _Moisture, int _Vitality, int _money): GameCharacter(_name, _money, _maxHp, _atk, _def), fullness(_Fullness), moisture(_Moisture), vitality(_Vitality) {
    currentRoom = nullptr;
    previousRoom = nullptr;
    equippedItem = nullptr;
    isRetreat = false;
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
    isRetreat = true;
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

void Player::updateTransitionState() {
    if (infectedPoison) {
        if (infectedPoison->getDuration() == 0) {
            infectedPoison = nullptr;
            return;
        }
        currentHp -= infectedPoison->getDamage();
        infectedPoison->decreaseDuration();
    }
    isRetreat = false;
}

void Player::eat(Food *food) {
    currentHp += food->getAddHp();
    if (currentHp > maxHp) currentHp = maxHp;
    fullness += food->getAddFullness();
    moisture += food->getAddMoisture();
    vitality += food->getAddVitality();
}

void Player::launchBattle(GameCharacter *enemy) {
    while (true) {
        cout << ("是否選擇撤退?\n"
                "1. 是\n"
                "2. 否\n"
                ">> ");
        int choice;
        cin >> choice;
        if (choice == 2) {
            retreat();
            return;
        }
        enemy->takeDamage(atk);
        cout << "你對" << enemy->getName() << "造成了" << atk - enemy->getDef() << "點傷害" << endl;
        if (enemy->checkIsDead()) {
            cout << "你贏了!" << endl;
            money += enemy->getMoney();
            cout << "你獲得了" << enemy->getMoney() << "元" << endl;
            if (enemy->getTag() == "monster") {
                if (dynamic_cast<Monster*>(enemy)->getDropItem()) {
                    addItem(dynamic_cast<Monster*>(enemy)->getDropItem());
                    cout << "你獲得了:" << dynamic_cast<Monster*>(enemy)->getDropItem()->getName() << "，已放入背包。"<< endl;
                }
            }
            break;
        }
        takeDamage(enemy->getAtk());
        cout << enemy->getName() << "對你造成了" << enemy->getAtk() - def << "點傷害" << endl;
        if (currentHp <= 0) {
            cout << "你輸了!" << endl;
            break;
        }
    }
}

void Player::triggerEvent(GameCharacter* gameCharacter) {
    launchBattle(gameCharacter);
}

void Player::updateEnvironmentDamage(int fullnessDamage, int moistureDamage, int vitalityDamage) {
    fullness -= fullnessDamage;
    moisture -= moistureDamage;
    vitality -= vitalityDamage;
    if (fullness < 0) fullness = 0;
    if (moisture < 0) moisture = 0;
    if (vitality < 0) vitality = 0;
}