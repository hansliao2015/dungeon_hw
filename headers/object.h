#pragma once

#include <iostream>
#include <string>
using namespace std;

class Object {
private:
    string name;
    string tag;
public:
    Object(string, string);
    string getName() const;
    string getTag() const;
};