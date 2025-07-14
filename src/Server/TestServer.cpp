#include "../../include/networking/server/TestServer.hpp"     // Fixed path
#include "../../include/networking/connection/Connection.hpp" // Fixed path
#include <iostream>
#include <netinet/in.h>
#include <unistd.h>

using namespace HDE;

TestServer::TestServer()
    : SimpleServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10),
      pool(4) // Create a ThreadPool with 4 threads
{
    router.add_route("/hello", [](const HTTPRequest&) {
        return Router::RouteResult{200, "ok","Hello from HDE TestServer!", "text/plain", {}};
    });

    router.add_route("/time", [](const HTTPRequest&) {
        return Router::RouteResult{200, "ok","Server time: " + std::to_string(time(nullptr)), "text/plain", {}};
    });

    router.add_route("/json", [](const HTTPRequest&) {
        return Router::RouteResult{200, "ok", R"({"status": "success", "message": "Hello, JSON!"})", "application/json", {}};
    });

    launch();
}

void TestServer::launch() {
    std::cout << "Server is running..." << std::endl;

    while (true) {
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        int client_sock = accept(
            get_socket()->get_socket(),
            (struct sockaddr*)&client_addr,
            &addr_len
        );

        if (client_sock < 0) {
            perror("accept");
            continue;
        }

        std::cout << "Client connected." << std::endl;

        pool.enqueue([client_sock, this]() {
            HDE::Connection conn(client_sock, router);
            conn.process();
        });
    }
}
