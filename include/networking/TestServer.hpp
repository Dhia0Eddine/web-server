#ifndef TESTSERVER_HPP
#define TESTSERVER_HPP

#include <signal.h>
#include <atomic>
#include "SimpleServer.hpp"
#include "../utils/logger.hpp"

namespace HDE {

class TestServer : public SimpleServer {
private:
    static std::atomic<bool> running;
    
    static void signal_handler(int signal) {
        Logger::log("Received signal " + std::to_string(signal) + ", shutting down...", Logger::INFO);
        running.store(false);
    }

public:
    TestServer(int domain, int service, int protocol, int port, u_long interface, int bcklg)
        : SimpleServer(domain, service, protocol, port, interface, bcklg) {}
    
    void launch() {
        signal(SIGINT, signal_handler);
        signal(SIGTERM, signal_handler);
        
        Logger::log("Server is running...", Logger::INFO);
        
        while (running.load()) {
            // Use select() or poll() with timeout instead of blocking accept()
            // This allows checking the running flag periodically
            
            // ...existing request handling code...
        }
        
        Logger::log("Server shutdown complete", Logger::INFO);
    }
};

// Static member definition
std::atomic<bool> TestServer::running{true};

}

#endif