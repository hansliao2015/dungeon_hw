#include "../headers/items.h"

Antidote::Antidote(string _name, int _money): Item(_name, _money, 0, 0, 0, 0, 0, 0) {
    this->setTag("Antidote");
}

void Antidote::use(Player *player) {
    player->useAntidote(this);
}