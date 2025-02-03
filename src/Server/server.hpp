#pragma once

#include "IServer.hpp"

#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

class Server final : public IServer {
    public:
        Server();
        ~Server() = default;

        void run() override;

    private:
        void initialize() override;

        void processData() override;

        void createSocket() override;

        void listenClient() override;
        
        uint16_t input_number;
        char input_data[1024];
        int server_fd, new_socket;
        struct sockaddr_in address;
        int opt;
        int addrlen;
};
