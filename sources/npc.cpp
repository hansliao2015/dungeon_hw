#include "../headers/gameCharacters.h"

Npc::Npc(int _index, string _line, string _name, int _money, int _maxHp, int _atk, int _def): index(_index), line(_line), items(), GameCharacter(_name, "Npc", _money, _maxHp, _atk, _def) {}


/*
`void triggerEvent(GameCharacter) override {`
	`cout << name << "和你開啟了對話";`
	`cout << name << ": " << "你好冒險者，想要和我交易嗎?"`
	`cout << "Option1: trade(交易), Option2: 默默離開, Option3: 開啟戰鬥"`
	`if (交易) trade()`
	`if (默默離開) print "歡迎下次光臨"`
	`if (開啟戰鬥) dynamic_cast<Player*>->triggerEvent(this)`
`}`
*/
void Npc::triggerEvent(GameCharacter* gameCharacter) {
    cout << getName() << "和你開啟了對話" << endl;
    cout << getName() << ": " << "你好冒險者，想要和我交易嗎?" << endl;
    cout << "Option1: 交易, Option2: 默默離開, Option3: 開啟戰鬥" << endl;
    cout << "請選擇你的選項:\n>> " << endl;
    int choice;
    cin >> choice;
    if (choice == 1) {
        trade(gameCharacter);
    } else if (choice == 2) {
        cout << getName() << ": 歡迎下次光臨" << endl;
    } else if (choice == 3) {
        Player *player = dynamic_cast<Player*>(gameCharacter);
        player->triggerEvent(this);
    }

}

void Npc::addItem(Item *item) { items.push_back(item); }

void Npc::speak() { cout << line << endl; }

void Npc::trade(GameCharacter* gameCharacter) {
    Player *player = dynamic_cast<Player*>(gameCharacter);
    cout << "商品:" << endl;
    for (int i = 0; i < items.size(); i++) {
        cout << i+1 << ". " << items[i]->getName() << " " << items[i]->getMoney() << "元" << endl;
    }
    cout << "請選擇你要的商品" << endl;
    int choice;
    cin >> choice;
    if (player->getMoney() > items[choice]->getMoney()) {
        player->setMoney(player->getMoney() - items[choice]->getMoney());
        player->addItem(items[choice]);
        cout << "看在買東西的份上，" << getName() << "好心的告訴你一些線索。" << endl;
        speak();
    } else {
        cout << "你的錢不夠，" << getName() << "不想和你交易了。" << endl;
    }
}