#include "../headers/gameCharacters.h"


GameCharacter::GameCharacter(string name, int mH, int a, int d): Object(name, "gameCharacter"), maxHp(mH), currentHp(mH), atk(a), def(d) {}

int GameCharacter::getMaxHp() const {return maxHp;}
int GameCharacter::getCurrentHp() const {return currentHp;}
int GameCharacter::getAtk() const {return atk;}
int GameCharacter::getDef() const {return def;}

void GameCharacter::takeDamage(int damage) {
    currentHp -= damage;
    if (currentHp < 0) currentHp = 0;
}

bool GameCharacter::checkIsDead() const {return currentHp <= 0;}
