#include "../headers/rooms.h"
#include "../headers/utils.h"

Forest::Forest(int _index): Room(_index) { this->tag = "森林"; }

void Forest::roomAction(Player *player) {
    if (player->getCurrentHp() <= 0) return;
    drawRoomAndPlayerState(player);
    cout << "這裡是房間" << this->getIndex() << endl;
    cout << "你來到了" << tag << "，因為徒步而行而感到飢餓，飽足-1\n";
    wait();
    player->updateEnvironmentDamage(1, 0, 0);
    bool isChangingRoom = showPlayerOptions(player);
    if (isChangingRoom) return;
    bool isLeaving = encounterObjects(player);
    if (isLeaving) return;
    if (getIsExit() && canPass()) {
        return;
    }
}