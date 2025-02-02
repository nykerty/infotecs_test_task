#include "IClient.hpp"
#include "client.hpp"
#include "task_lib.hpp"

#include <iostream>
#include <cstring>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <stdint.h>
#include <vector>

Client::Client() {
    initialize();
}

void Client::initialize() {
    t1 = std::thread(&Client::inputThread, this);
    t2 = std::thread(&Client::outputThread, this);
    ready = false;
}

void Client::run() {
    t1.join();
    t2.detach();
}

bool Client::isDigitsOnly(char* input)  {
    for (int i = 0; i < strlen(input); i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

void Client::inputCheck(char *input) {
    std::cout << "thread 1 input: ";
    std::cin >> input;

    if(strlen(input) <= 64 && isDigitsOnly(input))
        return;

    std::cout << "Invalid input. Please enter digits only and up to 64 characters." << std::endl;

    inputCheck(input);  
}

void Client::inputThread() {
    char input[64];
    while (true) {
        inputCheck(input);
        std::lock_guard<std::mutex> lock(mtx);
        inputProcess(input);
        strncpy(buffer, input, 128);
        std::cout << "thread 1 output: " << buffer << std::endl;
        ready = true;
        cv.notify_one();
    }
}

void Client::outputThread() {
    while (true) {
        std::unique_lock<std::mutex> lock(mtx);

        cv.wait(lock, [this]() { 
            return ready; 
        });

        uint16_t sum = 0;
        std::cout << "thread 2 input: " << buffer << std::endl;
        sum = sumDigits(buffer);
        std::cout << "thread 2 output: " << sum << std::endl;
        ready = false;
        memset(buffer, 0, sizeof(buffer));
        lock.unlock();
    }
}