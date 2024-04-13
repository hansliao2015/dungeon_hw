#include "../headers/dungeon.h"
#include "../headers/utils.h"

Dungeon::Dungeon() {}

bool Dungeon::isGameOver() {
    return ( isPlayerWin() || isPlayerLose());
}

bool Dungeon::isPlayerWin() {
    return player->getCurrentRoom()->getIsExit() && player->getCurrentRoom()->canPass();
}

bool Dungeon::isPlayerLose() {
    return player->checkIsDead();
}

void Dungeon::transition() {
    typewriter("移動至下個房間...\n");
    player->updateTransitionState();
    player->briefState();
}


void Dungeon::init() {
    cout << "遊戲初始化中..." << endl;
    initFoods();
    initNpcs();
    initMonsters();
    initRooms();
    initPlayer();
    player->setCurrentRoom(room);
    player->setPreviousRoom(room);
    cout << "遊戲初始化完成!" << endl;
}

void Dungeon::initPlayer() {
    cout << "請問你的名字是?" << endl;
    string name;
    cin >> name;
    player = new Player(name, 200, 20, 5, 100, 100, 100, 10);
}

void Dungeon::initFoods() {
    cout << "正在初始化食物..." << endl;
    foods.push_back(new Food("麵包", 5, 10, 10, 0, 5));
    foods.push_back(new Food("蘋果", 3, 5, 5, 8, 3));
    foods.push_back(new Food("肉湯", 10, 15, 15, 15, 15));
}

void Dungeon::initNpcs() {
    cout << "正在初始化NPC..." << endl;
    vector<string> npcLines;
    vector<string> npcNames;
    npcLines.push_back("小心毒蛇的攻擊。他們會在你身上留下猛毒!");
    npcLines.push_back("我曾去到傳說中的10號房間。那裏有著不可抵抗的強大怪物。");
    npcLines.push_back("喝下牛奶可以解除毒藥的效果!");
    npcLines.push_back("蘋果除了可以補充飽食度、水分，還可以補充血量!");
    npcNames.push_back("Derek");
    npcNames.push_back("Owen");
    npcNames.push_back("Allen");
    npcNames.push_back("Lily");
    for (int i = 0; i < 4; i++) {
        npcs.push_back(new Npc(i, npcLines[i], npcNames[i], 30, 30+10*i%3, 10-i%3, 2+i%3));
    }
}

void Dungeon::initMonsters() {
    cout << "正在初始化怪物..." << endl;
    monsters.push_back(new Monster("蛇", 30, 30, 5, 5));
    monsters.push_back(new Monster("蠍子", 25, 30, 10, 5));
    monsters.push_back(new Monster("狼", 100, 50, 15, 10));
    monsters.push_back(new Monster("森林之王", 150, 100, 15, 10));
}


void Dungeon::initRooms() {
    cout << "正在初始化房間..." << endl;
    vector<Room*> rooms;
    for (int i = 0; i <= 9; i++) {
        if (i%3 == 0) {
            rooms.push_back(new Room(i));
        } else if (i%3 == 1) {
            Forest *forest = new Forest(i);
            forest->addObject(foods[1]);
            forest->addObject(monsters[0]);
            rooms.push_back(forest);

        } else {
            Desert *desert = new Desert(i);
            desert->addObject(foods[0]);
            desert->addObject(monsters[1]);
            rooms.push_back(desert);
        }
    }
    room = rooms[0];
    Forest *forest = new Forest(10);
    forest->addObject(monsters[3]);
    rooms.push_back(forest);
    rooms[10]->setIsExit(true);
    /*
    Map:
          7-9-10
      3-5-6-8
      2-4
    0-1
    */
    rooms[0]->setRightRoom(rooms[1]);
    rooms[1]->setLeftRoom(rooms[0]);
    rooms[1]->setUpRoom(rooms[2]);
    rooms[2]->setDownRoom(rooms[1]);
    rooms[2]->setUpRoom(rooms[3]);
    rooms[2]->setRightRoom(rooms[4]);
    rooms[3]->setDownRoom(rooms[2]);
    rooms[3]->setRightRoom(rooms[5]);
    rooms[4]->setLeftRoom(rooms[2]);
    rooms[4]->setUpRoom(rooms[5]);
    rooms[5]->setLeftRoom(rooms[3]);
    rooms[5]->setDownRoom(rooms[4]);
    rooms[5]->setRightRoom(rooms[6]);
    rooms[6]->setLeftRoom(rooms[5]);
    rooms[6]->setUpRoom(rooms[7]);
    rooms[6]->setRightRoom(rooms[8]);
    rooms[7]->setDownRoom(rooms[6]);
    rooms[7]->setRightRoom(rooms[9]);
    rooms[8]->setLeftRoom(rooms[6]);
    rooms[8]->setUpRoom(rooms[9]);
    rooms[9]->setLeftRoom(rooms[7]);
    rooms[9]->setDownRoom(rooms[8]);
    rooms[9]->setRightRoom(rooms[10]);
    rooms[10]->setLeftRoom(rooms[9]);
}

/*

cin >> option;
if (option == move) {
	print "方向"
	if (撤退且前一個房間不等於後一個房間) 
		Player→retreat()
		dungeon.**playerMovedToAnotherRoom** = true
	if (通過)
		if room.canPass()
		Player→changeRoom(Room`*`)
		dungeon.**playerMovedToAnotherRoom** = true
} else if (option == checkStatus) {
detailedStatus
按下任意鍵以繼續，重新渲染
showOption()
} else if (option == openBackPack) {
listItem()
chooseItem()
printStatus
按下任意鍵以繼續，重新渲染
showOption()
}
*/
void Dungeon::handleMovement() {
    if (!player->getCurrentRoom()->canPass()) {
        cout << "這個房間裡有怪物，你只能選擇撤退，或是打倒怪物後繼續前進!" << endl;
        return;
    }
    cout << "請選擇方向" << endl;
    bool option1 = player->getCurrentRoom()->getUpRoom() && (player->getCurrentRoom()->getUpRoom() != player->getPreviousRoom());
    bool option2 = player->getCurrentRoom()->getDownRoom() && (player->getCurrentRoom()->getDownRoom() != player->getPreviousRoom());
    bool option3 = player->getCurrentRoom()->getLeftRoom() && (player->getCurrentRoom()->getLeftRoom() != player->getPreviousRoom());
    bool option4 = player->getCurrentRoom()->getRightRoom() && (player->getCurrentRoom()->getRightRoom() != player->getPreviousRoom());

    if (option1) 
        cout << "往上走(1)" << endl;
    if (option2)
      cout << "往下走(2)" << endl;
    if (option3)
       cout << "往左走(3)" << endl;
    if (option4)
      cout << "往右走(4)" << endl;
    cout << "撤退(5)" << endl;

    cout << ">> ";
    int direction;
    cin >> direction;
    if (direction == 1 && option1) {
        player->changeRoom(player->getCurrentRoom()->getUpRoom());
    } else if (direction == 2 && option2) {
        player->changeRoom(player->getCurrentRoom()->getDownRoom());
    } else if (direction == 3 && option3) {
        player->changeRoom(player->getCurrentRoom()->getLeftRoom());
    } else if (direction == 4 && option4) {
        player->changeRoom(player->getCurrentRoom()->getRightRoom());
    } else if (direction == 5) {
        player->retreat();
    } else {
        cout << "請選擇正確的方向!" << endl;
        handleMovement();
    }



}
void Dungeon::showOption() {
    cout << "你可以選擇..." << endl;
    cout << "1. 移動" << endl;
    cout << "2. 查看狀態" << endl;
    cout << "3. 打開背包" << endl;
    int option;
    cin >> option;
    if (option == 1) {
        handleMovement();
    } else if (option == 2) {
        player->detailedState();
        cout << "按下任意鍵以繼續..." << endl;
        cin.get();
        cin.get();
        showOption();
    } else if (option == 3) {
        player->openBackpack();
        showOption();
        cout << "按下任意鍵以繼續..." << endl;
        cin.get();
        cin.get();
    }
}
