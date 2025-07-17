#ifndef TEST_SERVER_HPP
#define TEST_SERVER_HPP

#include "SimpleServer.hpp"
#include <unistd.h>
#include <cstring>
#include <iostream>
#include <sys/types.h> // For socket types
#include <sys/socket.h> // For socket functions
#include <netinet/in.h> // For sockaddr_in
#include <signal.h>
#include <atomic>
#include "../../http/HTTPRequest.hpp"
#include "../../http/HTTPResponse.hpp"
#include "../threadpool/ThreadPool.hpp"
#include "../router/Router.hpp"
#include "../../utils/logger.hpp"
#include "../../utils/Config.hpp"

namespace HDE {
    class TestServer : public SimpleServer {
        public:
            // Constructor to create a test server with optional config file
            TestServer(const std::string& config_file = "server.conf");

            // Method to start the server
            void launch() override;

        private:
            static std::atomic<bool> running;
            
            static void signal_handler(int signal) {
                Logger::log("Received signal " + std::to_string(signal) + ", shutting down...", Logger::INFO);
                running.store(false);
            }
        
            Config config; // Configuration handler (must be first to initialize before others)
            ThreadPool pool; // Thread pool for handling requests
            Router router; // Router for handling HTTP requests
            
            // Helper method to setup routes
            void setup_routes();

        };
}

#endif