#include <iostream>
using namespace std;

#include "../headers/item.h"
#include "../headers/gameCharacter.h"

int main() {
    GameCharacter player("Player 1", 100, 10, 5);
    Item potion("Potion", 10, 0, 0);

    cout << "Player's health: " << player.getCurrentHp() << endl;
    cout << "Player's atk: " << player.getAtk() << endl;
    cout << "Player's def: " << player.getDef() << endl;
    
    return 0;
}