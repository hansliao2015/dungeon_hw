#include "../headers/gameCharacters.h"
#include "../headers/items.h"
#include "../headers/poison.h"

Monster::Monster(string _name, int _money, int _maxHp, int _atk, int _def, Item* _dropItem, Poison* _monsterPoison): GameCharacter(_name, "Monster", _money, _maxHp, _atk, _def), dropItem(_dropItem), monsterPoison(_monsterPoison) {}

Item* Monster::getDropItem() const { return dropItem; }

bool Monster::triggerEvent(GameCharacter* gameCharacter) {
    cout << "你遇到了" << getName() << "!" << endl;
    return dynamic_cast<Player*>(gameCharacter)->triggerEvent(this);
}

Poison* Monster::getMonsterPoison() const { return monsterPoison; }