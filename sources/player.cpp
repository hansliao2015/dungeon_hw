#include "../headers/gameCharacters.h"

Player::Player(string _name, int _maxHp, int _atk, int _def, int _Fullness, int _Moisture, int _Vitality, int _money): GameCharacter(_name, _money, _maxHp, _atk, _def), fullness(_Fullness), moisture(_Moisture), vitality(_Vitality) {
    currentRoom = nullptr;
    previousRoom = nullptr;
    equippedItem = nullptr;
    isRetreat = false;
}

Room* Player::getCurrentRoom() const { return currentRoom; }
Room* Player::getPreviousRoom() const { return previousRoom; }

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
    cout << "玩家: " << getName() << endl;
    cout << "血量: " << getCurrentHp() << "/" << getMaxHp() << endl;
    cout << "攻擊: " << getAtk() << endl;
    cout << "防禦: " << getDef() << endl;
    if (equippedItem) cout << "裝備: " << equippedItem->getName() << endl;
    else cout << "裝備: 無" << endl;
}

void Player::detailedState() {
    cout << "玩家: " << getName() << endl;
    cout << "血量: " << getCurrentHp() << "/" << getMaxHp() << endl;
    cout << "攻擊: " << getAtk() << endl;
    cout << "防禦: " << getDef() << endl;
    cout << "飽足: " << fullness << endl;
    cout << "滋潤: " << moisture << endl;
    cout << "精神: " << vitality << endl;
    if (infectedPoison) cout << "負面狀態--中毒: " << infectedPoison->getName() << endl;
    else cout << "負面狀態: 無" << endl;
    if (equippedItem) cout << "裝備: " << equippedItem->getName() << endl;
    else cout << "裝備: 無" << endl;
    cout << "背包內物品: " << endl;
    for (int i = 0; i < backpack.size(); i++) {
        cout << i + 1 << ". " << backpack[i]->getName() << endl;
    }
}

void Player::equip(Equipment *equipment) {
    cout << "你裝備了" << equipment->getName() << endl;
    equippedItem = equipment;
    briefState();
}

void Player::eat(Food *food) {
    cout << "你吃了" << food->getName() << endl;
    currentHp += food->getAddHp();
    if (currentHp > maxHp) currentHp = maxHp;
    fullness += food->getAddFullness();
    moisture += food->getAddMoisture();
    vitality += food->getAddVitality();
    briefState();
}

void Player::useAntidote(Antidote *antidote) {
    cout << "你使用了" << antidote->getName() << "，解除了中毒狀態" << endl;
    infectedPoison = nullptr;
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


void Player::launchBattle(GameCharacter *enemy) {
    while (true) {
        cout << ("是否選擇撤退?\n"
                "1. 是\n"
                "2. 否\n"
                ">> ");
        int choice;
        cin >> choice;
        if (choice == 1) {
            retreat();
            return;
        } else if (choice == 2) {
        } else {
            cout << "無效的選擇" << endl;
            continue;
        }
        enemy->takeDamage(atk);
        cout << "你對" << enemy->getName() << "造成了" << atk - enemy->getDef() << "點傷害" << endl;
        cout << enemy->getName() << "剩餘HP: " << enemy->getCurrentHp() << "/" << enemy->getMaxHp() << endl;
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
        cout << "你剩餘HP: " << currentHp << "/" << maxHp << endl;
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

void Player::listItems() {
    cout << "背包內物品: " << endl;
    for (int i = 0; i < backpack.size(); i++) {
        cout << i + 1 << ". " << backpack[i]->getName() << endl;
    }
}

void Player::chooseItem() {
    cout << "選擇要使用的物品: ";
    int choice;
    cin >> choice;
    if (choice < 1 || choice > backpack.size()) {
        cout << "無效的選擇" << endl;
        return;
    }
    backpack[choice - 1]->use(this);
    backpack.erase(backpack.begin() + choice - 1);
}

void Player::openBackpack() {
    listItems();
    chooseItem();
    briefState();
}