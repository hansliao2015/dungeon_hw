#include "../headers/utils.h"
#include <iostream>
#include <termios.h>
#include <unistd.h>

void wait() {
    std::cout << "按任意鍵繼續...\n";
    input();
}