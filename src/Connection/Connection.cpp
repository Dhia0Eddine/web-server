#include <unistd.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <thread>
#include "../../include/networking/connection/Connection.hpp"  // Fixed path
#include "../../include/http/HTTPResponse.hpp"                // Fixed path

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
}void Connection::send_response() {
    auto result = router.handle_request(request);

    HTTPResponse response;
    response.set_status(result.status_code, result.status_text);
    response.set_body(result.body);
    response.set_header("Connection", "close");
    response.set_header("Content-Type", result.content_type);
    response.set_header("Server", "HDE");

    for (const auto& [key, value] : result.additional_headers) {
        response.set_header(key, value);
    }

    std::string response_str = response.to_string();
    ssize_t bytes_sent = write(client_socket, response_str.c_str(), response_str.size());
    if (bytes_sent < 0) {
        perror("write");
    } else {
        std::cout << "Response sent to client.\n";
    }
}
