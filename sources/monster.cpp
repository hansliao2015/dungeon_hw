#include "../headers/gameCharacters.h"

Monster::Monster(string _name, int _money, int _maxHp, int _atk, int _def): GameCharacter(_name, "Monster", _money, _maxHp, _atk, _def) {}

Item* Monster::getDropItem() const { return dropItem; }

bool Monster::triggerEvent(GameCharacter* gameCharacter) {
    return dynamic_cast<Player*>(gameCharacter)->triggerEvent(this);
}