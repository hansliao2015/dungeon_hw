#include "../headers/items.h"
#include "../headers/gameCharacters.h"

Food::Food(string _name, int _money, int _addHp, int _addFullness, int _addMoisture, int _addVitality): Item(_name, _money, _addHp, 0, 0, _addFullness, _addMoisture, _addVitality) {}

void Food::use(Player* player) {
    player->eat(this);
}