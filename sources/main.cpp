#include <iostream>
using namespace std;

#include "../headers/items.h"
#include "../headers/gameCharacters.h"
#include "../headers/rooms.h"
#include "../headers/dungeon.h"
#include "../headers/utils.h"

int main() {
    Dungeon dungeon;
    dungeon.init();
    dungeon.runGame();
    dungeon.printResult();
    return 0;
}