#include "../headers/gameCharacter.h"

GameCharacter::GameCharacter(): Object(), maxHealth(0), currentHealth(0), attack(0), defense(0) {}
GameCharacter::GameCharacter(string name, int mH, int a, int d): Object(name, "gameCharacter"), maxHealth(mH), currentHealth(mH), attack(a), defense(d) {}

int GameCharacter::getMaxHealth() const {return maxHealth;}
int GameCharacter::getCurrentHealth() const {return currentHealth;}
int GameCharacter::getAttack() const {return attack;}
int GameCharacter::getDefense() const {return defense;}

void GameCharacter::setMaxHealth(int mH) {maxHealth = mH;}
void GameCharacter::setCurrentHealth(int cH) {currentHealth = cH;}
void GameCharacter::setAttack(int a) {attack = a;}
void GameCharacter::setDefense(int d) {defense = d;}

bool GameCharacter::checkIsDead() const {return currentHealth <= 0;}
void GameCharacter::takeDamage(int damage) {
    currentHealth -= damage;
    if (currentHealth < 0) currentHealth = 0;
}
