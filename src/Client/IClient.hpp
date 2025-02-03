#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>

class IClient {
    public:
        virtual ~IClient() = default;

        virtual void run() = 0;
    
    protected:
        virtual void initialize() = 0;
        
        virtual bool isDigitsOnly(char* input) = 0;
        virtual void inputCheck(char *input) = 0;

        virtual void inputThread() = 0;
        virtual void outputThread() = 0;
        virtual void processData() = 0;

        virtual void createSocket() = 0;
        virtual void checkServerStatus() = 0;
        virtual void connectToServer() = 0;
        virtual void sendMessage() = 0;
};