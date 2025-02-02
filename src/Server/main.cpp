#include "task_lib.hpp"
#include "server.hpp"

int main() {
    Server* server = new Server();

    server->run();

    delete server;

    return 0;
}