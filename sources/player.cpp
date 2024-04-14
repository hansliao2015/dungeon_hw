#include "../headers/gameCharacters.h"
#include "../headers/utils.h"

Player::Player(string _name, int _maxHp, int _atk, int _def, int _Fullness, int _Moisture, int _Vitality, int _money): GameCharacter(_name, _money, _maxHp, _atk, _def), fullness(_Fullness), moisture(_Moisture), vitality(_Vitality) {
    currentRoom = nullptr;
    previousRoom = nullptr;
    equippedItem = nullptr;
    isRetreat = false;
}

int Player::getFullness() const { return fullness; }
int Player::getMoisture() const { return moisture; }
int Player::getVitality() const { return vitality; }

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
    string n = (
        "玩家: " + getName() + "\n"
        "血量: " + to_string(getCurrentHp()) + "/" + to_string(getMaxHp()) + "\n"
        "攻擊: " + to_string(getAtk()) + "\n"
        "防禦: " + to_string(getDef()) + "\n"
    );
    if (equippedItem) n += "裝備: " + equippedItem->getName() + "\n";
    else n += "裝備: 無\n";
    typewriter(n);
}

void Player::detailedState() {

    string n = (
        "玩家: " + getName() + "\n"
        "血量: " + to_string(getCurrentHp()) + "/" + to_string(getMaxHp()) + "\n"
        "攻擊: " + to_string(getAtk()) + "\n"
        "防禦: " + to_string(getDef()) + "\n"
        "飽足: " + to_string(fullness) + "\n"
        "滋潤: " + to_string(moisture) + "\n"
        "精神: " + to_string(vitality) + "\n"
    );
    if (infectedPoison) n += "負面狀態--中毒: " + infectedPoison->getName() + "\n";
    else {
        n += "負面狀態: 無";
        n += "\n";
    }
    if (equippedItem) {
        n += "裝備: " + equippedItem->getName() + "\n";
    } else {
        n += "裝備: 無";
        n += "\n";
    }
    n += "背包內物品: " ;
    for (int i = 0; i < backpack.size(); i++) {
        n += backpack[i]->getName() + " ";
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
        typewriter("輸入q以離開戰鬥\n");
        typewriter("輸入a以攻擊\n");
        char choice = input();
        if (choice == 'q') {
            retreat();
            break;
        } else if (choice == 'a') {
            typewriter("你對" + enemy->getName() + "發動了攻擊\n");
        } else {
            typewriter("無效的選擇\n");
            continue;
        }
        enemy->takeDamage(atk);
        typewriter("你對" + enemy->getName() + "造成了" + to_string(atk - enemy->getDef()) + "點傷害\n");
        typewriter(enemy->getName() + "剩餘HP: " + to_string(enemy->getCurrentHp()) + "/" + to_string(enemy->getMaxHp()) + "\n");

        if (enemy->checkIsDead()) {
            typewriter("你贏了!\n");
            money += enemy->getMoney();
            typewriter("你獲得了" + to_string(enemy->getMoney()) + "元\n");
            if (enemy->getTag() == "monster") {
                if (dynamic_cast<Monster*>(enemy)->getDropItem()) {
                    addItem(dynamic_cast<Monster*>(enemy)->getDropItem());
                    typewriter("你獲得了" + dynamic_cast<Monster*>(enemy)->getDropItem()->getName() + "，已放入背包。\n");
                }
            }
            break;
        }
        takeDamage(enemy->getAtk());
        typewriter("你剩餘HP: " + to_string(currentHp) + "/" + to_string(maxHp) + "\n");
        typewriter(enemy->getName() + "對你造成了" + to_string(enemy->getAtk() - def) + "點傷害\n");
        if (currentHp <= 0) {
            typewriter("你死了!\n");
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

void Player::openBackpack() {
    if (backpack.size() == 0) {
        cout << ("背包內沒有物品\n");
        return;
    }
    cout << ("背包內物品: \n");
    for (int i = 0; i < backpack.size(); i++) {
        typewriter(to_string(i + 1) + ". " + backpack[i]->getName() + "\n");
    }
    cout << ("選擇要使用的物品: ");
    int choice;
    cin >> choice;
    if (choice < 1 || choice > backpack.size()) {
        typewriter("無效的選擇\n");
        return;
    }
    backpack[choice - 1]->use(this);
    backpack.erase(backpack.begin() + choice - 1);
    briefState();
}