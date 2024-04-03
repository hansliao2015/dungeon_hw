#include "../headers/object.h"


Object::Object(): name(""), tag("") {}
Object::Object(string n, string t): name(n), tag(t) {}

void Object::setName(string n) {name = n;}
void Object::setTag(string t) {tag = t;}

string Object::getName() const {return name;}
string Object::getTag() const {return tag;}