#include "../headers/item.h"

Item::Item(): Object(), addHealth(0), addAttack(0), addDefense(0) {}
Item::Item(string name, int aH, int aA, int aD): Object(name, "item"), addHealth(aH), addAttack(aA), addDefense(aD) {}

int Item::getAddHealth() const {return addHealth;}
int Item::getAddAttack() const {return addAttack;}
int Item::getAddDefense() const {return addDefense;}

void Item::setAddHealth(int aH) {addHealth = aH;}
void Item::setAddAttack(int aA) {addAttack = aA;}
void Item::setAddDefense(int aD) {addDefense = aD;}