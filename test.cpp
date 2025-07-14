#include "include/networking/server/TestServer.hpp"
#include <stdio.h>

int main() {
    // Create an instance of the TestServer
    HDE::TestServer server;

    // The server will run indefinitely, handling requests
    // To stop the server, you would typically need to implement a signal handler or a shutdown mechanism
    return 0; // Exit code
}
// Note: The server will run indefinitely, so you may need to manually terminate it (e.g., Ctrl+C in the terminal).
// In a real-world application, you would implement proper shutdown logic to gracefully stop the server.    
