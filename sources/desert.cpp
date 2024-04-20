#include "../headers/rooms.h"
#include "../headers/utils.h"

Desert::Desert(int _index): Room(_index) { this->tag = "沙漠"; }

void Desert::roomAction(Player *player) {
    if (player->getCurrentHp() <= 0) return;
    drawRoomAndPlayerState(player);
    cout << "這裡是房間" << this->getIndex() << endl;
    cout << "你來到了" << tag << "，這裡的環境非常惡劣。你的飽足-1，滋潤-2\n";
    wait();
    player->updateEnvironmentDamage(1, 2, 0);
    bool isChangingRoom = showPlayerOptions(player);
    if (isChangingRoom) return;
    bool isLeaving = encounterObjects(player);
    if (isLeaving) return;
    if (getIsExit() && canPass()) {
        cout << "你找到了出口的房間，離開了dungeon" << tag << endl;
        wait();
        return;
    }
    bool isChangingRoom2 = showPlayerOptions(player);
    if (isChangingRoom2) return;
}