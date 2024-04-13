#include "../headers/rooms.h"

Forest::Forest(int _index): Room(_index) {}

void Forest::roomAction(Player *player) {
    cout << "你來到了森林，因為徒步而行而感到飢餓，飽足-1";
    player->updateEnvironmentDamage(1, 0, 0);
    encounterObjects(player);
}