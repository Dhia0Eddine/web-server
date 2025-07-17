#include <iostream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

class HTTPClient {
public:
    static void sendRequest(const std::string& method, const std::string& path, 
                           const std::string& body = "", const std::string& contentType = "text/plain") {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            std::cerr << "Socket creation failed\n";
            return;
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(8080);
        inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);

        if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
            std::cerr << "Connection failed\n";
            close(sock);
            return;
        }

        std::string request = method + " " + path + " HTTP/1.1\r\n";
        request += "Host: localhost:8080\r\n";
        request += "Content-Type: " + contentType + "\r\n";
        request += "Content-Length: " + std::to_string(body.length()) + "\r\n";
        request += "Connection: close\r\n";
        request += "\r\n";
        request += body;

        send(sock, request.c_str(), request.length(), 0);

        char buffer[4096];
        int bytes_received = recv(sock, buffer, sizeof(buffer) - 1, 0);
        if (bytes_received > 0) {
            buffer[bytes_received] = '\0';
            std::cout << "=== " << method << " " << path << " ===\n";
            std::cout << buffer << "\n\n";
        }

        close(sock);
    }
};

int main() {
    std::cout << "Testing HTTP Methods:\n\n";

    // Test GET
    HTTPClient::sendRequest("GET", "/hello");
    HTTPClient::sendRequest("GET", "/users");

    // Test POST
    HTTPClient::sendRequest("POST", "/users", 
        R"({"name": "Alice", "email": "alice@example.com"})", "application/json");
    HTTPClient::sendRequest("POST", "/login", 
        R"({"username": "admin", "password": "secret"})", "application/json");

    // Test PUT
    HTTPClient::sendRequest("PUT", "/users/1", 
        R"({"name": "Bob Updated", "email": "bob@updated.com"})", "application/json");

    // Test DELETE
    HTTPClient::sendRequest("DELETE", "/users/1");

    return 0;
}
