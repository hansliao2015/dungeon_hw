#include "../headers/object.h"


Object::Object(): name("") {}
Object::Object(string n): name(n) {}

string Object::getName() const {return name;}
void Object::setName(string n) {name = n;}
