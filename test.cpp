#include "include/networking/server/TestServer.hpp"
#include <stdio.h>

int main() {
    // Create an instance of the TestServer with configuration file
    HDE::TestServer server("server.conf");

    // The server will run and handle requests based on the configuration
    // It will gracefully shutdown when receiving SIGINT (Ctrl+C) or SIGTERM
    return 0; // Exit code
}
