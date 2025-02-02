#pragma once

#include "IServer.hpp"

#include <stdint.h>

class Server final : public IServer {
    public:
        Server();
        ~Server() = default;

        void run() override;

    private:
        void initialize() override;

        void processData() override;
        
        uint16_t input_number;
};