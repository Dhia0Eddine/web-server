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
    // Parse request and store in class field
    current_request = HTTPRequest::parse(std::string(buffer));

    // Log for debug
    std::cout << "----- Parsed HTTP Request -----\n";
    std::cout << "Method: " << current_request.method << "\n";
    std::cout << "Path: " << current_request.path << "\n";
    std::cout << "Version: " << current_request.http_version << "\n";
    std::cout << "Headers:\n";
    for (const auto& [key, value] : current_request.headers) {
        std::cout << "  " << key << ": " << value << "\n";
    }
    std::cout << "Body:\n" << current_request.body << "\n";
    std::cout << "--------------------------------\n";
}

void HDE::TestServer::responder() {
    std::string body;
    std::string content_type = "text/plain";
    int status_code = 200;
    std::string status_text = "OK";

    if (current_request.path == "/hello") {
        body = "Hello from HDE TestServer!";
    } else if (current_request.path == "/time") {
        body = "Server time: " + std::to_string(time(nullptr));
    } else if (current_request.path == "/json") {
        content_type = "application/json";
        body = R"({"status": "success", "message": "Hello, JSON!"})";
    } else {
        status_code = 404;
        status_text = "Not Found";
        body = "404 - Resource not found.";
    }

    std::string response =
        "HTTP/1.1 " + std::to_string(status_code) + " " + status_text + "\r\n" +
        "Content-Type: " + content_type + "\r\n" +
        "Content-Length: " + std::to_string(body.size()) + "\r\n" +
        "Connection: close\r\n" +
        "\r\n" +
        body;

    ssize_t bytes_sent = write(client_socket, response.c_str(), response.size());
    if (bytes_sent < 0) {
        perror("write");
    }

    close(client_socket);
    std::cout << "Response sent to client and connection closed.\n";
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
