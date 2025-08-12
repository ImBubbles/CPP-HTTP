#include <iostream>
#include <string>

#include "server/Server.h"

int main() {

    Server httpServer;

    while (true) {
        std::string response;
        std::cin >> response;
        if (response == "exit" || response == "quit" || response == "kill" || response == "stop") {
            return 0;
        }
    }

    return 0;

}