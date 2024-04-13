#include "../headers/gameCharacters.h"


GameCharacter::GameCharacter(string name, int _money, int mH, int a, int d): Object(name, "gameCharacter"), money(_money), maxHp(mH), currentHp(mH), atk(a), def(d) {}

GameCharacter::GameCharacter(string name, string tag, int _money, int mH, int a, int d): Object(name, tag), money(_money), maxHp(mH), currentHp(mH), atk(a), def(d) {}

int GameCharacter::getMoney() const {return money;}
int GameCharacter::getMaxHp() const {return maxHp;}
int GameCharacter::getCurrentHp() const {return currentHp;}
int GameCharacter::getAtk() const {return atk;}
int GameCharacter::getDef() const {return def;}

void GameCharacter::setMoney(int _money) {money = _money;}

void GameCharacter::takeDamage(int damage) {
    damage -= def;
    currentHp -= damage;
    if (currentHp < 0) currentHp = 0;
}

bool GameCharacter::checkIsDead() const {return currentHp <= 0;}
