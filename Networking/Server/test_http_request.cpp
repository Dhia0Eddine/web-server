#include "HTTPRequest.hpp"
#include <iostream>

int main() {
    std::string raw_request =
        "GET /hello HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "User-Agent: curl/7.68.0\r\n"
        "Accept: */*\r\n"
        "\r\n"
        "body=ignored_now";

    HDE::HTTPRequest req = HDE::HTTPRequest::parse(raw_request);

    std::cout << "Method: " << req.method << "\n";
    std::cout << "Path: " << req.path << "\n";
    std::cout << "Version: " << req.http_version << "\n";
    std::cout << "Headers:\n";
    for (const auto& [key, value] : req.headers) {
        std::cout << key << ": " << value << "\n";
    }
    std::cout << "Body:\n" << req.body << "\n";

    return 0;
}
// This code snippet demonstrates how to parse an HTTP request string using the HTTPRequest class.
// It prints the method, path, HTTP version, headers, and body of the request to the console.
// The example request is a simple GET request to "/hello" with some headers and an ignored body.
// The output will show the parsed components of the HTTP request, confirming that the parsing works