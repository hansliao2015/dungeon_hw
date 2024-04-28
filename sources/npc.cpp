#include "../headers/gameCharacters.h"
#include "../headers/utils.h"

Npc::Npc(int _index, string _line, string _name, int _money, int _maxHp, int _atk, int _def): index(_index), line(_line), items(), GameCharacter(_name, "Npc", _money, _maxHp, _atk, _def) {}

bool Npc::triggerEvent(GameCharacter* gameCharacter) {
    Player *player = dynamic_cast<Player*>(gameCharacter);
    player->getCurrentRoom()->drawRoomAndPlayerState(player);
    cout << getName() << "和你開啟了對話" << endl;
    typewriter(getName() + ": " + "你好冒險者，想要和我交易嗎?\n");
    typewriter(
        "Option1: 交易\n"
        "Option2: 默默離開\n"
        "Option3: 開啟戰鬥\n"
    );
    cout << "請選擇你的選項:\n>> ";
    char choice = input();
    if (choice == '1') {
        trade(gameCharacter);
        return false;
    } else if (choice == '2') {
        cout << getName() << ": 歡迎下次光臨" << endl;
        return false;
    } else if (choice == '3') {
        Player *player = dynamic_cast<Player*>(gameCharacter);
        if (player->triggerEvent(this)) return true;
    } else {
        cout << "無效的選擇!" << endl;
        triggerEvent(gameCharacter);
    }
    return false;

}

void Npc::addItem(Item *item) { items.push_back(item); }

void Npc::speak() {
    cout << getName() << ": ";
    cout << line << endl;
    wait();
}

void Npc::trade(GameCharacter* gameCharacter) {
    Player *player1 = dynamic_cast<Player*>(gameCharacter);
    player1->getCurrentRoom()->drawRoomAndPlayerState(player1);
    if (items.size() == 0) {
        cout << getName() << "的商品賣完了!" << endl;
        return;
    }
    Player *player = dynamic_cast<Player*>(gameCharacter);
    cout << "目前金錢剩餘:" << player->getMoney() << "元" << endl;
    cout << "商品:" << endl;
    string itemsStr = "";
    for (int i = 0; i <= items.size(); i++) {
        if (i == items.size()) {
            itemsStr += to_string(i+1) + ". 取消交易\n";
            break;
        }
        itemsStr += to_string(i+1) + ". " + items[i]->getName() + ": " + to_string(items[i]->getMoney()) + "元\n";
    }
    typewriter(itemsStr);
    cout << "請選擇你要的商品:\n>> ";
    char choice = input();
    int index = choice - '0';
    if (index < 1 || index > items.size() + 1) {
        cout << "無效的選擇!" << endl;
        trade(gameCharacter);
    } else if (index == items.size() + 1) {
        return;
    } else if (player->getMoney() >= items[index - 1]->getMoney()) {
        player->setMoney(player->getMoney() - items[index - 1]->getMoney());
        player->addItem(items[index - 1]);
        cout << "交易成功，你花了" << items[index - 1]->getMoney() << "元" << endl;
        typewriter("看在買東西的份上，" + getName() + "好心的告訴你一些線索。" + '\n');
        speak();
        trade(gameCharacter);
    } else {
        cout << "你的金錢不足!";
        wait();
    }
}