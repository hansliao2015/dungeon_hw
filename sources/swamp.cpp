#include "../headers/rooms.h"
#include "../headers/utils.h"
#include "../headers/poison.h"

Swamp::Swamp(int _index): Room(_index) { this->tag = "沼澤"; }

void Swamp::roomAction(Player *player) {
    if (player->getCurrentHp() <= 0) return;
    drawRoomAndPlayerState(player);
    typewriter("這裡是房間" + to_string(this->getIndex()) + "\n");
    typewriter("你來到了" + tag + "，這裡有惡臭的沼氣，讓你昏昏欲睡。\n你陷入了中毒的負面狀態!\n");
    wait();
    player->updateEnvironmentDamage(1, 2, 0);
    player->setInfectedPoison(new Poison("沼澤之毒", 10, 3));
    bool isChangingRoom = showPlayerOptions(player);
    if (isChangingRoom) return;
    bool isLeaving = encounterObjects(player);
    if (isLeaving) return;
    if (getIsExit() && canPass()) {
        cout << "你找到了出口的房間，離開了dungeon" << tag << endl;
        wait();
        return;
    }
}