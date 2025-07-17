#include <unistd.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include <sys/socket.h>
#include <thread>
#include "../../include/networking/connection/Connection.hpp"
#include "../../include/http/HTTPResponse.hpp"
#include "../../include/utils/logger.hpp"

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
    Logger::log("Connection closed", Logger::INFO);
}

void Connection::read_request() {
    ssize_t bytes_read = read(client_socket, buffer, sizeof(buffer) - 1);
    if (bytes_read < 0) {
        Logger::log("Read failed: " + std::string(strerror(errno)), Logger::ERROR);
        return;
    }
    buffer[bytes_read] = '\0';
    Logger::log("Received:\n" + std::string(buffer), Logger::DEBUG);

    request = HTTPRequest::parse(std::string(buffer));
}

void Connection::handle_request() {
    Logger::log("----- Parsed HTTP Request -----", Logger::DEBUG);
    Logger::log("Method: " + request.method, Logger::DEBUG);
    Logger::log("Path: " + request.path, Logger::DEBUG);
    Logger::log("Version: " + request.http_version, Logger::DEBUG);
    Logger::log("Headers:", Logger::DEBUG);
    for (const auto& [key, value] : request.headers) {
        Logger::log("  " + key + ": " + value, Logger::DEBUG);
    }
    Logger::log("Body:\n" + request.body, Logger::DEBUG);
    Logger::log("--------------------------------", Logger::DEBUG);
}

void Connection::send_response() {
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
        Logger::log("Write failed: " + std::string(strerror(errno)), Logger::ERROR);
    } else {
        Logger::log("Response sent to client", Logger::INFO);
    }
}
