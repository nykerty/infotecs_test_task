#include "server.hpp"
#include "task_lib.hpp"

#include <iostream>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

Server::Server() {
    initialize();
}

void Server::initialize() {
    input_number = 0;
    opt = 1;
    addrlen = sizeof(address);

    createSocket();
}

void Server::run() {
    listenClient();

    close(new_socket);
    close(server_fd);
}

void Server::processData() {
    input_number = atoi(input_data);
        
    if (checkNumber(input_number)) {
        std::cout << "Received number: " << input_number << ", a multiple of 32." << std::endl;
    } else {
        std::cout << "Received number: " << input_number << ", a NON multiple of 32." << std::endl;
    }

    memset(input_data, 0, sizeof(input_data));
}

void Server::createSocket() {
        // Создание сокета
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Настройка параметров сокета
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    // Привязка сокета к порту
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }
}

void Server::listenClient() {
        // Прослушивание входящих подключений
    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port 8080..." << std::endl;

    while (true) {
        int new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        if (new_socket < 0) {
            perror("accept failed");
            continue; // Продолжаем ждать подключения
        }

        std::cout << "[Connection established!]" << std::endl;

        while (true) {
            int input_number = read(new_socket, input_data, 1024);
            if (input_number <= 0) {
                std::cout << "[Client disconnected]" << std::endl;
                std::cout << "[Server is listening on port 8080...]" << std::endl;
                break; // Клиент отключился, выходим из цикла обработки
            }
            
            std::string health = std::to_string(1);
            ssize_t bytes_sent = send(new_socket, health.c_str(), health.size(), 0);

            processData();
        }

        // Закрытие сокета клиента
        close(new_socket);
    }
}