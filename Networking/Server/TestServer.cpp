#include "TestServer.hpp"
#include <string>
#include <iostream>
#include "HTTPRequest.hpp"

HDE::TestServer::TestServer() : SimpleServer(AF_INET, SOCK_STREAM, 0, 8080, INADDR_ANY, 10) {
   launch();
}
void HDE::TestServer::accepter() {
    struct sockaddr_in client_addr = get_socket()->get_address();
    printf(client_addr.sin_family == AF_INET ? "IPv4" : "IPv6");
    std::cout << " - Accepting connections on port " << ntohs(client_addr.sin_port) << std::endl;

    socklen_t addr_len = sizeof(client_addr);

   
    client_socket = accept(get_socket()->get_socket(), (struct sockaddr*)&client_addr, &addr_len);
    if (client_socket < 0) {
        perror("accept");
        return;
    }
    std::cout << "Client connected." << std::endl;

    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("read");
    } else {
        buffer[bytes_read] = '\0';
        std::cout << "Received:\n" << buffer << std::endl;
    }
}
void HDE::TestServer::handler() {
    // Parse the request from the buffer using our structured parser
    HTTPRequest req = HTTPRequest::parse(std::string(buffer));

    // Log structured information
    std::cout << "----- Parsed HTTP Request -----\n";
    std::cout << "Method: " << req.method << "\n";
    std::cout << "Path: " << req.path << "\n";
    std::cout << "Version: " << req.http_version << "\n";
    std::cout << "Headers:\n";
    for (const auto& [key, value] : req.headers) {
        std::cout << "  " << key << ": " << value << "\n";
    }
    std::cout << "Body:\n" << req.body << "\n";
    std::cout << "--------------------------------\n";
}


void HDE::TestServer::responder() {
    std::string response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/plain\r\n"
        "Content-Length: 17\r\n"
        "\r\n"
        "Hello from server";

    ssize_t bytes_sent = write(client_socket, response.c_str(), response.size());
    if (bytes_sent < 0) {
        perror("write");
    }

    close(client_socket);
    std::cout << "Response sent to client and connection closed." << std::endl;
}

void HDE::TestServer::launch() {
    std::cout << "Server is running..." << std::endl;

    while (true) {
        std::cout << "Waiting for a connection..." << std::endl;

        accepter();  // Accept a new connection
        handler();   // Process request (empty for now)
        responder(); // Send response
    }
}
