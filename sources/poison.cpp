#include "../headers/poison.h"

Poison::Poison(string _name, int _damage, int _maxDuration): name(_name), damage(_damage), maxDuration(_maxDuration), duration(_maxDuration) {}

string Poison::getName() { return name; }
int Poison::getDamage() { return damage; }
int Poison::getDuration() { return duration; }
void Poison::decreaseDuration() { duration--; }
void Poison::infect(Player* player) {
    duration = maxDuration;
    player->setInfectedPoison(this);
}