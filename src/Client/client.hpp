#pragma once

#include "IClient.hpp"

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

        std::thread t1;
        std::thread t2;
        std::mutex mtx;
        std::condition_variable cv;

        bool ready;
        char buffer[128];
};
