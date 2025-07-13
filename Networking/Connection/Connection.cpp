#include "Connection.hpp"
#include <unistd.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <thread>

using namespace HDE;

Connection::Connection(int client_socket, Router& router)
    : client_socket(client_socket), router(router) {
    memset(buffer, 0, sizeof(buffer));
}

void Connection::process() {
    read_request();
    handle_request();
    send_response();
    close(client_socket);
    std::cout << "Connection closed.\n";
}

void Connection::read_request() {
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        perror("read");
        return;
    }
    buffer[bytes_read] = '\0';
    std::cout << "Received:\n" << buffer << std::endl;

    request = HTTPRequest::parse(std::string(buffer));
}

void Connection::handle_request() {
    std::cout << "----- Parsed HTTP Request -----\n";
    std::cout << "Method: " << request.method << "\n";
    std::cout << "Path: " << request.path << "\n";
    std::cout << "Version: " << request.http_version << "\n";
    std::cout << "Headers:\n";
    for (const auto& [key, value] : request.headers) {
        std::cout << "  " << key << ": " << value << "\n";
    }
    std::cout << "Body:\n" << request.body << "\n";
    std::cout << "--------------------------------\n";
}

void Connection::send_response() {
    auto [status_code, body] = router.handle_request(request);

    std::string status_text = (status_code == 200) ? "OK" : "Not Found";
    std::string content_type = (request.path == "/json") ? "application/json" : "text/plain";

    std::string response =
        "HTTP/1.1 " + std::to_string(status_code) + " " + status_text + "\r\n" +
        "Content-Type: " + content_type + "\r\n" +
        "Content-Length: " + std::to_string(body.size()) + "\r\n" +
        "Connection: close\r\n"
        "\r\n" +
        body;

    ssize_t bytes_sent = write(client_socket, response.c_str(), response.size());
    if (bytes_sent < 0) {
        perror("write");
    } else {
        std::cout << "Response sent to client.\n";
    }
}
