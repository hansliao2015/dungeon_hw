#include "../headers/gameCharacters.h"
#include "../headers/utils.h"
#include "../headers/rooms.h"

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
    detailedState();
}

void Player::detailedState() {
    getCurrentRoom()->drawRoomAndPlayerState(this);
    string n = (
        "玩家: " + getName() + "\n"
    );
    
    if (equippedItem) {
        n += (
            "血量: " + to_string(getCurrentHp()) + "/" + to_string(getMaxHp()) + "(" + equippedItem->getName() + "+" + to_string(equippedItem->getAddHp()) + ")\n"
            "攻擊: " + to_string(getAtk()) + "(" + equippedItem->getName() + "+" + to_string(equippedItem->getAddAtk()) + ")\n"
            "防禦: " + to_string(getDef()) + "(" + equippedItem->getName() + "+" + to_string(equippedItem->getAddDef()) + ")\n"
        );
    } else {
        n += (
            "血量: " + to_string(getCurrentHp()) + "/" + to_string(getMaxHp()) + "\n"
            "攻擊: " + to_string(getAtk()) + "\n"
            "防禦: " + to_string(getDef()) + "\n"
        );
    }
    n += (
        "飽足: " + to_string(fullness) + "\n"
        "滋潤: " + to_string(moisture) + "\n"
        "精神: " + to_string(vitality) + "\n"
        "金錢: " + to_string(money) + "\n"
    );
    if (infectedPoison) n += "負面狀態--中毒: " + infectedPoison->getName() + "，剩下" + to_string(infectedPoison->getDuration()) + "回合\n";
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
    if (backpack.size() == 0) n += "無\n";
    else {
        for (int i = 0; i < backpack.size(); i++) {
            n += backpack[i]->getName() + " ";
        }
        n += "\n";
    }
    typewriter(n);
}

void Player::equip(Equipment *equipment) {
    cout << "你裝備了" << equipment->getName() << endl;
    maxHp += equipment->getAddHp();
    currentHp += equipment->getAddHp();
    atk += equipment->getAddAtk();
    def += equipment->getAddDef();
    equippedItem = equipment;
}

void Player::eat(Food *food) {
    getCurrentRoom()->drawRoomAndPlayerState(this);
    cout << "你吃了" << food->getName() << endl;
    currentHp += food->getAddHp();
    fullness += food->getAddFullness();
    moisture += food->getAddMoisture();
    vitality += food->getAddVitality();
    if (currentHp > maxHp) currentHp = maxHp;
    if (fullness > 10) fullness = 10;
    if (moisture > 10) moisture = 10;
    if (vitality > 10) vitality = 10;
    typewriter("你的狀態提升了!\n");
    typewriter("血量:" + to_string(currentHp) + "/" + to_string(maxHp) + " (+" + to_string(food->getAddHp()) + ")\n");
    typewriter("飽足:" + to_string(fullness) + "/" + to_string(10) + " (+" + to_string(food->getAddFullness()) + ")\n");
    typewriter("滋潤:" + to_string(moisture) + "/" + to_string(10) + " (+" + to_string(food->getAddMoisture()) + ")\n");
    typewriter("精神:" + to_string(vitality) + "/" + to_string(10) + " (+" + to_string(food->getAddVitality()) + ")\n");
}

void Player::useAntidote(Antidote *antidote) {
    cout << "你使用了" << antidote->getName() << "，解除了中毒狀態" << endl;
    infectedPoison = nullptr;
}

void Player::setCurrentRoom(Room *room) { currentRoom = room; }

void Player::setPreviousRoom(Room *room) { previousRoom = room; }

void Player::setInfectedPoison(Poison *poison) { infectedPoison = poison; }

void Player::updatePosionDamage() {
    if (infectedPoison) {
        if (infectedPoison->getDuration() == 0) {
            infectedPoison = nullptr;
            return;
        }
        currentHp -= infectedPoison->getDamage();
        infectedPoison->decreaseDuration();
        typewriter("受到毒的影響，你的體力下降，hp減少" + to_string(infectedPoison->getDamage()) + "\n");
        if (infectedPoison->getDuration() == 0) typewriter("你解除了中毒狀態\n");
        else typewriter("毒的持續效果還有" + to_string(infectedPoison->getDuration()) + "回合\n");
    }
    isRetreat = false;
}


bool Player::launchBattle(GameCharacter *enemy) {
    typewriter("輸入1以攻擊\n");
    typewriter("輸入2以離開戰鬥\n");
    while (true) {
        char choice = input();
        if (choice == '2') {
            retreat();
            return true;
        } else if (choice == '1') {
        } else {
            typewriter("無效的選擇\n");
            continue;
        }
        enemy->takeDamage(atk);
        cout << "你對" + enemy->getName() + "造成了" + to_string(atk - enemy->getDef()) + "點傷害\n";
        cout << enemy->getName() + "剩餘HP: " + to_string(enemy->getCurrentHp()) + "/" + to_string(enemy->getMaxHp()) + "\n";

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
            if (getCurrentRoom()->getIsExit() && getCurrentRoom()->canPass()) {
                typewriter("你找到了出口的房間，離開了dungeon\n");
                wait();
                return true;
            }
            wait();
            return false;
        }
        takeDamage(enemy->getAtk());
        if (dynamic_cast<Monster*>(enemy)) {
            dynamic_cast<Monster*>(enemy)->getMonsterPoison()->infect(this);
            typewriter(enemy->getName() + "的攻擊附帶了" + dynamic_cast<Monster*>(enemy)->getMonsterPoison()->getName() + "，你受到了中毒的負面狀態!\n");
        }
        updatePosionDamage();
        typewriter(enemy->getName() + "對你造成了" + to_string(enemy->getAtk() - def) + "點傷害\n");
        typewriter("你剩餘HP: " + to_string(currentHp) + "/" + to_string(maxHp) + "\n");
        if (currentHp <= 0) {
            typewriter("你死了!\n");
            wait();
            return true;
        }
    }
    return false;
}

bool Player::triggerEvent(GameCharacter* gameCharacter) {
    return launchBattle(gameCharacter);
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
    cout << ("選擇要使用的物品: \n");
    cout << ("輸入q以離開背包\n");
    char choice = input();
    if (choice == 'q') {
        return;
    } else if (choice < '1' || choice > backpack.size() + '0') {
        typewriter("無效的選擇\n");
        return;
    } else {
        backpack[(choice - '0') - 1]->use(this);
        backpack.erase(backpack.begin() + (choice -'0') - 1);
        wait();
        openBackpack();
    }
    briefState();
}