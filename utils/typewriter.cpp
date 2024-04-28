#include <iostream>
#include <unistd.h>
#include <string>

#include "../headers/utils.h"
using namespace std;

int TIME = 1;
string ANSI_RESET = "\033[0m";
string ANSI_YELLOW = "\033[33m";
string ANSI_GREEN = "\033[32m";
string ANSI_BLUE = "\033[34m";
string ANSI_RED = "\033[31m";
string ANSI_WHITE = "\033[97m";

void typewriter(string text) {
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        fflush(stdout);
        // usleep means microsecond, so 1000 means 1ms
        usleep(TIME * 1000);
        // when time = 30, it means 30ms
    }
}

void red(string text) {
    cout << ANSI_RED;
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        fflush(stdout);
        usleep(TIME * 1000);
    }
    cout << ANSI_RESET;
}

void blue(string text) {
    cout << ANSI_BLUE;
    for (int i = 0; i < text.length(); i++) {
        cout << text[i];
        fflush(stdout);
        usleep(TIME * 1000);
    }
    cout << ANSI_RESET;
}