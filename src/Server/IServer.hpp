#pragma once

class IServer {
    public:
        virtual ~IServer() = default;

        virtual void run() = 0;
    
    protected:
        virtual void initialize() = 0;
        
        virtual void processData() = 0;
};