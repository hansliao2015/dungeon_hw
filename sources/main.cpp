#include <iostream>
using namespace std;

#include "../headers/item.h"

int main() {
    Item item("Sword", 10, 5, 3);
    cout << "Name: " << item.getName() << endl;
    cout << "Tag: " << item.getTag() << endl;
    cout << "Add Health: " << item.getAddHealth() << endl;
    cout << "Add Attack: " << item.getAddAttack() << endl;
    cout << "Add Defense: " << item.getAddDefense() << endl;
    return 0;
}