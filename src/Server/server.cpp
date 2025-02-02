#include "server.hpp"
#include "task_lib.hpp"

#include <iostream>

Server::Server() {
    initialize();
}

void Server::initialize() {
    input_number = 0;
}

void Server::run() {
    processData();
}

void Server::processData() {
    while (true) {
        std::cout << "wait for number: ";
        std::cin >> input_number;

        if (checkNumber(input_number)) {
            std::cout << "TRUE" << std::endl;
        } else {
            std::cout << "FALSE" << std::endl;
        }

    }
}