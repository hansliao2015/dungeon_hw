#pragma once

#include <iostream>
#include <string>
using namespace std;

class Object {
private:
    string name;
public:
    Object();
    Object(string);
    string getName() const;
    void setName(string);
};