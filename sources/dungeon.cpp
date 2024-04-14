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



void Dungeon::init() {
    clear();
    cout << ("遊戲初始化中...\n");
    initFoods();
    initNpcs();
    initMonsters();
    initRooms();
    initPlayer();
    player->setCurrentRoom(room);
    player->setPreviousRoom(room);
    cout << ("遊戲初始化完成!\n");
}

void Dungeon::initPlayer() {
    cout << ("請問你的名字是?\n");
    string name;
    cin >> name;
    player = new Player(name, 200, 20, 5, 100, 100, 100, 10);
}

void Dungeon::initFoods() {
    cout << ("正在初始化食物...\n");
    foods.push_back(new Food("麵包", 5, 10, 10, 0, 5));
    foods.push_back(new Food("蘋果", 3, 5, 5, 8, 3));
    foods.push_back(new Food("肉湯", 10, 15, 15, 15, 15));
}

void Dungeon::initNpcs() {
    cout << ("正在初始化NPC...\n");
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
    cout << ("正在初始化怪物...\n");
    monsters.push_back(new Monster("蛇", 30, 30, 5, 5));
    monsters.push_back(new Monster("蠍子", 25, 30, 10, 5));
    monsters.push_back(new Monster("狼", 100, 50, 15, 10));
    monsters.push_back(new Monster("森林之王", 150, 100, 15, 10));
}


void Dungeon::initRooms() {
    cout << ("正在初始化房間...\n");
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
    rooms[1]->addObject(npcs[0]);
    rooms[2]->addObject(npcs[1]);
    rooms[4]->addObject(npcs[2]);
    rooms[5]->addObject(npcs[3]);
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

void Dungeon::handleMovement() {
    if (!player->getCurrentRoom()->canPass()) {
        typewriter("這個房間裡有怪物，你只能選擇回到原本房間，或是打倒怪物後繼續前進!\n");
    }
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
        handleMovement();
    }



}
void Dungeon::showOption() {
    string n = (
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
        handleMovement();
    } else if (choice == '2') {
        player->detailedState();
        wait();
        drawGameConsole();
    } else if (choice == '3') {
        player->openBackpack();
        wait();
        drawGameConsole();
    } else if (choice == '4') {
        return;
    } else {
        cout << "你按下了" << choice << "，請選擇正確的選項!\n"; 
        typewriter("請選擇正確的選項!\n");
        wait();
        showOption();
    }
}

void Dungeon::printResult() {
    typewriter("遊戲結束!\n");
    if (isPlayerWin()) {
        typewriter("恭喜你通過了地下城!\n");
    } else if (isPlayerLose()){
        typewriter("你輸了!\n");
    }
}

void Dungeon::runGame() {
    while (!isGameOver()) {
        drawGameConsole();
        if (isGameOver()) break;
        
    }
}

void Dungeon::drawGameConsole() {
    clear();
    cout << "---------------------------------------------------------------------\n";
    cout << "           " << player->getCurrentRoom()->getIndex() << "號房間:" << player->getCurrentRoom()->tag << endl;
    if (player->getCurrentRoom()->getUpRoom()) {
        cout << "                   ↑                  " << endl;
        cout << "                                      " << endl;
        cout << "    ███████████████ ███████████████   " <<  "  玩家: " << player->getName() << endl;
    }
    else {
        cout << "                                      " << endl;
        cout << "                                      " << endl;
        cout << "    ███████████████████████████████   " <<  "  玩家: " << player->getName() << endl;
    }
    cout << "    █                             █   " <<  "  血量: " << player->getCurrentHp() << "/" << player->getMaxHp() << endl;  
    cout << "    █                             █   " <<  "  攻擊: " << player->getAtk() << endl;
    cout << "    █                             █   " <<  "  防禦: " << player->getDef() << endl;
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
    cout << "                                      " << endl;
    cout << "---------------------------------------------------------------------\n";
    
    player->getCurrentRoom()->roomAction(player);
    showOption();
}


