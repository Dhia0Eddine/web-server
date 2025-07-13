#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include "SimpleServer.hpp"
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sys/types.h> // For socket types
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include "HTTPRequest.hpp"
#include "../ThreadPool/ThreadPool.hpp"

namespace HDE {
    class TestServer : public SimpleServer {
        public:
            // Constructor to create a test server
            TestServer();

            // Method to start the server
            void launch() override;

        private:
        
            // Implement the required methods for the server
            void accepter() override;
            void handler() override;
            void responder() override;
            char buffer[30000]; // Buffer for reading data
            int client_socket; // Socket for the client connection
            HTTPRequest current_request; // Current HTTP request
            ThreadPool pool; // Thread pool for handling requests
            void handle_client(int client_socket);

            
        };
}

#endif