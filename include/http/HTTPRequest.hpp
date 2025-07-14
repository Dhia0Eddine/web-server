
#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <string>
#include <unordered_map>

namespace HDE {
class HTTPRequest {
public:
    std::string method;
    std::string path;
    std::string http_version;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

    static HTTPRequest parse(const std::string& raw_request);
};
}

#endif // HTTP_REQUEST_HPP


// This file defines the HTTPRequest class, which is responsible for parsing and storing HTTP request data
// It includes the method, path, HTTP version, headers, and body of the request.   