#include "../headers/rooms.h"

Forest::Forest(int _index): Room(_index) { this->tag = "Forest"; }

void Forest::roomAction(Player *player) {
    cout << "這裡是房間" << this->getIndex() << endl;
    cout << "你來到了森林，因為徒步而行而感到飢餓，飽足-1";
    player->updateEnvironmentDamage(1, 0, 0);
    encounterObjects(player);
}