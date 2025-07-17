#include "../../include/networking/server/TestServer.hpp"     // Fixed path
#include "../../include/networking/connection/Connection.hpp" // Fixed path
#include "../../include/utils/logger.hpp"
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>
#include <signal.h>
#include <sys/select.h>
#include <atomic>
#include <errno.h>
#include <cstring>

using namespace HDE;

// Static member definition
std::atomic<bool> TestServer::running{true};

TestServer::TestServer()
    : SimpleServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10),
      pool(4) // Create a ThreadPool with 4 threads
{
    // GET routes
    router.get("/hello", [](const HTTPRequest&) {
        return Router::RouteResult{200, "OK", "Hello from GET!", "text/plain", {}};
    });

    router.get("/users", [](const HTTPRequest&) {
        return Router::RouteResult{200, "OK", 
            R"([{"id": 1, "name": "John"}, {"id": 2, "name": "Jane"}])", 
            "application/json", {}};
    });

    // POST routes
    router.post("/users", [](const HTTPRequest& req) {
        return Router::RouteResult{201, "Created", 
            R"({"id": 3, "name": "New User", "body": ")" + req.body + R"("})", 
            "application/json", {}};
    });

    router.post("/login", [](const HTTPRequest& req) {
        return Router::RouteResult{200, "OK", 
            R"({"token": "abc123", "message": "Login successful", "received": ")" + req.body + R"("})", 
            "application/json", {}};
    });

    // PUT routes
    router.put("/users/1", [](const HTTPRequest& req) {
        return Router::RouteResult{200, "OK", 
            R"({"id": 1, "name": "Updated User", "body": ")" + req.body + R"("})", 
            "application/json", {}};
    });

    // DELETE routes
    router.delete_("/users/1", [](const HTTPRequest&) {
        return Router::RouteResult{200, "OK", 
            R"({"message": "User deleted successfully"})", 
            "application/json", {}};
    });

    launch();
}

void TestServer::launch() {
    // Set up signal handlers
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    Logger::log("Server is running...", Logger::INFO);

    while (running.load()) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        // Use select() to make accept() non-blocking with timeout
        fd_set read_fds;
        FD_ZERO(&read_fds);
        FD_SET(get_socket()->get_socket(), &read_fds);
        
        struct timeval timeout;
        timeout.tv_sec = 1;  // 1 second timeout
        timeout.tv_usec = 0;
        
        int select_result = select(get_socket()->get_socket() + 1, &read_fds, nullptr, nullptr, &timeout);
        
        if (select_result < 0) {
            if (errno == EINTR) {
                // Interrupted by signal, continue to check running flag
                continue;
            }
            Logger::log("Select failed: " + std::string(strerror(errno)), Logger::ERROR);
            continue;
        }
        
        if (select_result == 0) {
            // Timeout occurred, continue to check running flag
            continue;
        }
        
        // Socket is ready for accept()
        int client_sock = accept(
            get_socket()->get_socket(),
            (struct sockaddr*)&client_addr,
            &addr_len
        );

        if (client_sock < 0) {
            Logger::log("Accept failed: " + std::string(strerror(errno)), Logger::ERROR);
            continue;
        }

        Logger::log("Client connected", Logger::INFO);

        pool.enqueue([client_sock, this]() {
            HDE::Connection conn(client_sock, router);
            conn.process();
        });
    }
    
    Logger::log("Server shutdown complete", Logger::INFO);
}
