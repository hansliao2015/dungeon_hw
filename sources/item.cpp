#include "../headers/items.h"

Item::Item(string _name, int _money, int _addHp, int _addAtk, int _addDef, int _addFullness, int _addMoisture, int _addVitality): Object(_name, "Item"), money(_money), addHp(_addHp), addAtk(_addAtk), addDef(_addDef), addFullness(_addFullness), addMoisture(_addMoisture), addVitality(_addVitality) {}

int Item::getMoney() const { return money; }
int Item::getAddHp() const { return addHp; }
int Item::getAddAtk() const { return addAtk; }
int Item::getAddDef() const { return addDef; }
int Item::getAddFullness() const { return addFullness; }
int Item::getAddMoisture() const { return addMoisture; }
int Item::getAddVitality() const { return addVitality; }

