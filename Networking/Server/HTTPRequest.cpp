#include "HTTPRequest.hpp"
#include <sstream>
#include <algorithm>

using namespace HDE;

HTTPRequest HTTPRequest::parse(const std::string& raw_request) {
    HTTPRequest req;
    std::istringstream stream(raw_request);
    std::string line;

    // Parse request line
    if (std::getline(stream, line)) {
        line.erase(std::remove(line.end()-1, line.end(), '\r'), line.end());
        std::istringstream line_stream(line);
        line_stream >> req.method >> req.path >> req.http_version;
    }

    // Parse headers
    while (std::getline(stream, line) && line != "\r") {
        line.erase(std::remove(line.end()-1, line.end(), '\r'), line.end());
        if (line.empty()) break;

        auto colon_pos = line.find(':');
        if (colon_pos != std::string::npos) {
            std::string key = line.substr(0, colon_pos);
            std::string value = line.substr(colon_pos + 1);
            value.erase(0, value.find_first_not_of(" "));
            req.headers[key] = value;
        }
    }

    // Parse body (if any)
    std::string body_content((std::istreambuf_iterator<char>(stream)),
                             std::istreambuf_iterator<char>());
    req.body = body_content;

    return req;
}
