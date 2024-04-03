#include <iostream>
using namespace std;

#include "../headers/item.h"
#include "../headers/gameCharacter.h"

int main() {
    GameCharacter player("Player 1", 100, 10, 5);
    Item potion("Potion", 10, 0, 0);

    cout << "Player's health: " << player.getCurrentHealth() << endl;
    cout << "Player's attack: " << player.getAttack() << endl;
    cout << "Player's defense: " << player.getDefense() << endl;
    
    return 0;
}