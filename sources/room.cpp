#include "../headers/rooms.h"
#include "../headers/utils.h"

Room::Room(int _index): index(_index), tag("空房間"), upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr), isExit(false), objects() {}

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
    drawRoomAndPlayerState(player);
    typewriter("這裡是房間" + to_string(this->getIndex()) + "\n");
    typewriter("在這裡你不會遇到任何東西，可以安心地調整狀態，休息過後再出發。\n");
    wait();
    showPlayerOptions(player);
}

bool Room::canPass() {
    bool canPass = true;
    for (auto object: this->objects) {
        if (object->getTag() == "Monster") {
            canPass = false;
            break;
        }
    }
    return canPass;
}

//Room不會用到encounterObjects()
bool Room::encounterObjects(Player *player) {
    for (int i = 0; i < this->objects.size(); i++) {
        if (player->checkIsDead()) return true;
        drawRoomAndPlayerState(player);
        cout << "玩家移動中…" << endl;
        cout << "前方有" << this->objects[i]->getTag() << "，是否選擇繼續向前?" << endl;
        cout << "你可以選擇:" << endl;
        cout << "1. 繼續向前" << endl;
        cout << "2. 退回上個房間" << endl;
        bool noMonster = true;
        for (int j = 0; j < this->objects.size(); j++) {
            if (this->objects[j]->getTag() == "Monster") {
                noMonster = false;
                break;
            }
        }
        if (noMonster) {
            cout << "3. 移動至新的房間" << endl;
            return true;
        }
        char option = input();
        if (option == '1') {
            if (dynamic_cast<Item*>(this->objects[i])) {
                drawRoomAndPlayerState(player);
                cout << "是否選擇將" << this->objects[i]->getName() << "放入背包?" << endl;
                cout << "1. 是" << endl;
                cout << "2. 否" << endl;
                option = input();
                if (option == '1') {
                    player->addItem(dynamic_cast<Item*>(this->objects[i]));
                    cout << "你獲得了" << this->objects[i]->getName() << "，已放入背包。" << endl;
                    this->objects.erase(this->objects.begin() + i);
                    --i;
                } else if (option == '2') {
                    cout << "你選擇忽略" << this->objects[i]->getName() << "。" << endl;
                } else {
                    cout << "無效的選擇" << endl;
                }
            } 
            else if (dynamic_cast<GameCharacter*>(this->objects[i])) {
                drawRoomAndPlayerState(player);
                if (dynamic_cast<GameCharacter*>(this->objects[i])->triggerEvent(player)) {
                    return true;
                }
                if (static_cast<GameCharacter*>(this->objects[i])->checkIsDead()) {
                    this->objects.erase(this->objects.begin() + i);
                    --i;
                }
            }
        }
        if (option == '2') {
            cout << "你選擇退回上個房間。" << endl;
            player->changeRoom(player->getPreviousRoom());
            return true;
        }
        if (noMonster && option == '3') {
            cout << "你選擇移動至新的房間。" << endl;
            handlePlayerMovements(player);
        }
        if (i == this->objects.size()-1) cout << "你走到了房間的盡頭。" << endl;
    }
    return false;
}

void Room::drawRoomAndPlayerState(Player *player) {
    clear();
    cout << "---------------------------------------------------------------------\n";
    cout << "           " << player->getCurrentRoom()->getIndex() << "號房間:" << player->getCurrentRoom()->tag << endl;
    if (player->getCurrentRoom()->getUpRoom()) {
        cout << "                   ↑                  " << endl;
        cout << "                                      " << endl;
        cout << "    ███████████████ ███████████████   " << endl;
    }
    else {
        cout << "                                      " << endl;
        cout << "                                      " << endl;
        cout << "    ███████████████████████████████   " << endl;
    }
    cout << "    █                             █   " << endl;  
    cout << "    █                             █   " << endl;
    cout << "    █                             █   " << endl;
    cout << "    █                             █   " << endl;
    cout << "    █                             █   " << endl;
    if (player->getCurrentRoom()->getLeftRoom() && player->getCurrentRoom()->getRightRoom())
    cout << "←                                   → " << endl;
    else if (player->getCurrentRoom()->getLeftRoom())
    cout << "←                                 █   " << endl;
    else if (player->getCurrentRoom()->getRightRoom())
    cout << "    █                               → " << endl;
    else
    cout << "    █                             █   " << endl; 
    cout << "    █                             █   " << endl;
    cout << "    █                             █   " << endl;
    cout << "    █                             █   " << endl;
    cout << "    █                             █   " << endl;
    cout << "    █                             █   " << endl;
    if (player->getCurrentRoom()->getDownRoom()) {
        cout << "    ███████████████ ███████████████   " << endl;
        cout << "                                      " << endl;
        cout << "                   ↓                  " << endl;
    }
    else {
        cout << "    ███████████████████████████████   " << endl;
        cout << "                                      " << endl;
        cout << "                                      " << endl;
    }
    if (player->getCurrentRoom()->getObjects().size() > 0) {
        cout << "出現順序: ";
        for (auto object: player->getCurrentRoom()->getObjects()) {
            cout << object->getTag() << " ";
        }
        cout << endl;
    } else {
        cout << "                                      " << endl;
    }
    cout << "                                      " << endl;
    cout << "---------------------------------------------------------------------\n";
}

bool Room::showPlayerOptions(Player *player) {
    drawRoomAndPlayerState(player);
    if (player->checkIsDead()) return true;
    string n = "debug: function Room::showPlayerOptions()\n";
    if (player->getCurrentRoom()->tag == "空房間") {
        n = (
            "你可以選擇...\n"
            "1. 移動至別的房間\n"
            "2. 查看狀態\n"
            "3. 打開背包\n>> "
        );
        typewriter(n);
        char choice;
        choice = input();
        if (choice == '1') {
            handlePlayerMovements(player);
        } else if (choice == '2') {
            player->detailedState();
            wait();

        } else if (choice == '3') {
            player->openBackpack();
            wait();
            player->getCurrentRoom()->drawRoomAndPlayerState(player);

        } else {
            cout << "你按下了" << choice << "，請選擇正確的選項!\n"; 
            typewriter("請選擇正確的選項!\n");
            wait();
            showPlayerOptions(player);
        }
    }
    else if (player->getCurrentRoom()->tag == "森林" || player->getCurrentRoom()->tag == "沙漠") {
        n = (
            "你可以選擇...\n"
            "1. 移動至別的房間\n"
            "2. 查看狀態\n"
            "3. 打開背包\n"
            "4. 繼續前行\n>> "
        );
        
        
        typewriter(n);
        char choice;
        choice = input();
        if (choice == '1') {
            handlePlayerMovements(player);
        } else if (choice == '2') {
            player->detailedState();
            wait();
            return true;

        } else if (choice == '3') {
            player->openBackpack();
            wait();
            return true;

        } else if (choice == '4') {
            return false;
        } else {
            cout << "你按下了" << choice << "，請選擇正確的選項!\n"; 
            typewriter("請選擇正確的選項!\n");
            wait();
            showPlayerOptions(player);
        }
        
    }
    return false;

}

void Room::handlePlayerMovements(Player *player) {
    drawRoomAndPlayerState(player);
    if (!player->getCurrentRoom()->canPass()) {
        typewriter("提示: 這個房間裡有怪物，打倒怪物前，你只能往回走!\n");
        typewriter("你可以選擇...\n");
        typewriter("往回走(1)\n");
        typewriter("繼續前行(2)\n");
        char direction = input();
        if (direction == '1') {
            player->changeRoom(player->getPreviousRoom());
        } else if (direction == '2') {
            return;
        } else {
            typewriter("請選擇正確的選項!\n");
            handlePlayerMovements(player);
        }

    } else {
        typewriter("你可以選擇...\n");
            
        bool option1 = player->getCurrentRoom()->getUpRoom();
        bool option2 = player->getCurrentRoom()->getDownRoom();
        bool option3 = player->getCurrentRoom()->getLeftRoom();
        bool option4 = player->getCurrentRoom()->getRightRoom();

        if (option1) 
            typewriter("往上走(1)\n");
        if (option2)
            typewriter("往下走(2)\n");
        if (option3)
            typewriter("往左走(3)\n");
        if (option4)
            typewriter("往右走(4)\n");

        char direction = input();
        if (direction == '1' && option1) {
            player->changeRoom(player->getCurrentRoom()->getUpRoom());
        } else if (direction == '2' && option2) {
            player->changeRoom(player->getCurrentRoom()->getDownRoom());
        } else if (direction == '3' && option3) {
            player->changeRoom(player->getCurrentRoom()->getLeftRoom());
        } else if (direction == '4' && option4) {
            player->changeRoom(player->getCurrentRoom()->getRightRoom());
        } else {
            typewriter("請選擇正確的方向!\n");
            handlePlayerMovements(player);
        }

    }

}