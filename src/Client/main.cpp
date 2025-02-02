#include "task_lib.hpp"
#include "client.hpp"

#include <iostream>

int main() {
    Client* client = new Client();

    client->run();

    delete client;

    return 0;
}