#include "../headers/items.h"
#include "../headers/gameCharacters.h"

class Player;

Equipment::Equipment(string _name, int _money, int _addHp, int _addAtk, int _addDef, int _addFullness, int _addMoisture, int _addVitality): Item(_name, _money, _addHp, _addAtk, _addDef, _addFullness, _addMoisture, _addVitality) {}

void Equipment::use(Player* player) {
    player->equip(this);
}