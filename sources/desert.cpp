#include "../headers/rooms.h"

Desert::Desert(int _index): Room(_index) { this->tag = "沙漠"; }

void Desert::roomAction(Player *player) {
    drawRoomAndPlayerState(player);
    cout << "這裡是房間" << this->getIndex() << endl;
    cout << "你來到了" << tag << "，這裡的環境非常惡劣。你的飽足-1，滋潤-2\n";
    player->updateEnvironmentDamage(1, 2, 0);
    encounterObjects(player);
    showPlayerOptions(player);
}