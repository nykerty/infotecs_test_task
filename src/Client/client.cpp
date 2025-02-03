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

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

Client::Client() {
    initialize();
}

void Client::initialize() {
    sock = 0;
    createSocket();
    t1 = std::thread(&Client::inputThread, this);
    t2 = std::thread(&Client::outputThread, this);
    ready = false;
    connected = false;
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

    connectToServer();

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

        processData();
        
        sendMessage();

        lock.unlock();
    }

    close(sock);
}

void Client::processData() {
    sum = 0;
    std::cout << "thread 2 input: " << buffer << std::endl;
    sum = sumDigits(buffer);

    std::cout << "thread 2 output: " << sum << std::endl;
    ready = false;
    memset(buffer, 0, sizeof(buffer));
}

void Client::createSocket() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        std::cerr << "[Socket creation error]" << std::endl;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Преобразование IPv4-адреса в формат сети
    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        std::cerr << "[Invalid address/ Address not supported]" << std::endl;
    }
}

void Client::connectToServer() {
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cerr << "[Server isnt responding]" << std::endl;
        close(sock);
        return;
    }

    std::cout << "[Connected to server!]" << std::endl;
    connected = true;  
}    

void Client::checkServerStatus() {        
    int valread = read(sock, buffer, 1024);
    if (valread <= 0) {
        std::cout << "[Server is disconnected, connection attempt...]" << std::endl;
        close(sock);
        connected = false; // Переходим в режим повторного подключения
        return;
    }
}

void Client::sendMessage() {
    std::string message = std::to_string(sum);
        send(sock, message.c_str(), message.size(), 0);

        checkServerStatus();
        if (!connected) {
            connectToServer();
        }
}
