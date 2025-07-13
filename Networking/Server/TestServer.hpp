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
#include "../Router/Router.hpp"

namespace HDE {
    class TestServer : public SimpleServer {
        public:
            // Constructor to create a test server
            TestServer();

            // Method to start the server
            void launch() override;

        private:
        
            ThreadPool pool; // Thread pool for handling requests
            Router router; // Router for handling HTTP requests

        };
}

#endif