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
    virtual ~Object();
    string getName() const;
    string getTag() const;
};