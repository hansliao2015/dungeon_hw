#pragma once

#include <iostream>
#include <string>
using namespace std;

class Object {
private:
    string name;
    string tag;
public:
    Object();
    Object(string, string);
    void setName(string);
    void setTag(string);
    string getName() const;
    string getTag() const;
};