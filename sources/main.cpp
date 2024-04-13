#include <iostream>
using namespace std;

#include "../headers/items.h"
#include "../headers/gameCharacters.h"
#include "../headers/rooms.h"
#include "../headers/dungeon.h"

int main() {
    Dungeon dungeon;
    dungeon.init();
    cout << "歡迎來到地下城" << endl;
    while (!dungeon.isGameOver()) {
        dungeon.transition();
        dungeon.isPlayerChangeRoom = false;
        if (dungeon.isGameOver()) break;
        dungeon.showOption();
        if (dungeon.isPlayerChangeRoom) continue;
        dungeon.player->getCurrentRoom()->roomAction(dungeon.player);
        if (dungeon.isPlayerChangeRoom) continue;
        if (dungeon.player->getCurrentRoom()->tag != "Room") dungeon.showOption();
    }
    cout << "遊戲結束。" << endl;
    if (dungeon.isPlayerLose()) {
        cout << "你輸了。" << endl;
    } else if (dungeon.isPlayerWin()){
        cout << "你贏了。" << endl;
    }

    return 0;
}