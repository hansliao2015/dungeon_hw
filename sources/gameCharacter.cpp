#include "../headers/gameCharacter.h"


GameCharacter::GameCharacter(string name, int mH, int a, int d): Object(name, "gameCharacter"), maxHealth(mH), currentHp(mH), atk(a), def(d) {}

int GameCharacter::getMaxHp() const {return maxHealth;}
int GameCharacter::getCurrentHp() const {return currentHp;}
int GameCharacter::getAtk() const {return atk;}
int GameCharacter::getDef() const {return def;}

void GameCharacter::updateState(int hp, int atk, int def) {
    currentHp += hp;
    atk += atk;
    def += def;
}

bool GameCharacter::checkIsDead() const {return currentHp <= 0;}
void GameCharacter::takeDamage(int damage) {
    currentHp -= damage;
    if (currentHp < 0) currentHp = 0;
}
