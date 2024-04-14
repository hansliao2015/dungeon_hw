#include "../headers/rooms.h"
#include "../headers/utils.h"

Room::Room(int _index): index(_index), tag("普通房間"), upRoom(nullptr), downRoom(nullptr), leftRoom(nullptr), rightRoom(nullptr), isExit(false), objects() {}

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
    typewriter("這裡是房間" + to_string(this->getIndex()) + "\n");
    typewriter("在這裡你不會遇到任何東西，可以安心地調整狀態，休息過後再出發。\n");
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
void Room::encounterObjects(Player *player) {
    for (int i = 0; i < this->objects.size(); i++) {
        if (player->checkIsDead()) return;
        cout << "玩家移動中…" << endl;
        cout << "前方有" << this->objects[i]->getTag() << "，是否選擇繼續向前?" << endl;
        cout << "你可以選擇:" << endl;
        cout << "1. 繼續向前" << endl;
        cout << "2. 退回上個房間" << endl;
        char option = input();
        if (option == '1') {
            if (dynamic_cast<Item*>(this->objects[i])) {
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
                dynamic_cast<GameCharacter*>(this->objects[i])->triggerEvent(player);
                if (static_cast<GameCharacter*>(this->objects[i])->checkIsDead()) {
                    this->objects.erase(this->objects.begin() + i);
                    --i;
                }
            }
        }
        if (option == '2') {
            cout << "你選擇退回上個房間。" << endl;

        }
        if (i == this->objects.size()-1) cout << "你走到了房間的盡頭。" << endl;
    }
}
