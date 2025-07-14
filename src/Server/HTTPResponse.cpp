#include "../../include/http/HTTPResponse.hpp"  // Fixed path
#include <sstream>
using namespace HDE;

HTTPResponse::HTTPResponse(int status_code, std::string status_text)
    : status_code(status_code), status_text(std::move(status_text)) {}

void HTTPResponse::set_header(const std::string& key, const std::string& value) {
    headers[key] = value;
}

void HTTPResponse::set_body(const std::string& body_content) {
    body = body_content;
    headers["Content-Length"] = std::to_string(body.size());
}

std::string HTTPResponse::to_string() const {
    std::ostringstream response_stream;
    response_stream << "HTTP/1.1 " << status_code << " " << status_text << "\r\n";
    for (const auto& [key, value] : headers) {
        response_stream << key << ": " << value << "\r\n";
    }
    response_stream << "\r\n" << body;
    return response_stream.str();
}

void HTTPResponse::set_status(int status_code, const std::string& status_text) {
    this->status_code = status_code;
    this->status_text = status_text;
}