#include "../headers/object.h"


Object::Object(string n, string t): name(n), tag(t) {}
Object::~Object() {}

string Object::getName() const { return name; }
string Object::getTag() const { return tag; }
