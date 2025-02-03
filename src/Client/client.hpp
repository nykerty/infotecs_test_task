#pragma once

#include "IClient.hpp"

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdint.h>

class Client final : public IClient {
    public:
        Client();
        ~Client() = default;

        void run() override;

    private:
        void initialize() override;

        bool isDigitsOnly(char* input) override;
        void inputCheck(char *input) override;
        
        void inputThread() override;
        void outputThread() override;
        void processData() override;

        void createSocket() override;
        void checkServerStatus() override;
        void connectToServer() override;
        void sendMessage() override;

        std::thread t1;
        std::thread t2;
        std::mutex mtx;
        std::condition_variable cv;

        uint16_t sum;
        bool ready;
        bool connected;
        char buffer[1024] = {0};

        int sock;
        struct sockaddr_in serv_addr;
};
