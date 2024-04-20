#include "../headers/rooms.h"

Forest::Forest(int _index): Room(_index) { this->tag = "森林"; }

void Forest::roomAction(Player *player) {
    drawRoomAndPlayerState(player);
    cout << "這裡是房間" << this->getIndex() << endl;
    cout << "你來到了" << tag << "，因為徒步而行而感到飢餓，飽足-1\n";
    player->updateEnvironmentDamage(1, 0, 0);
    if (player->getCurrentHp() <= 0) return;
    while (showPlayerOptions(player));
    bool isLeaving = encounterObjects(player);
    if (isLeaving) return;
    showPlayerOptions(player);
}