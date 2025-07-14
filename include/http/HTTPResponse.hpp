#ifndef HDE_HTTPRESPONSE_HPP
#define HDE_HTTPRESPONSE_HPP

#include <string>
#include <unordered_map>

namespace HDE {

class HTTPResponse {
private:
    int status_code;
    std::string status_text;
    std::unordered_map<std::string, std::string> headers;
    std::string body;

public:
    HTTPResponse(int status_code = 200, std::string status_text = "OK");

    void set_header(const std::string& key, const std::string& value);
    void set_body(const std::string& body_content);
    void set_status(int status_code, const std::string& status_text);
    std::string to_string() const;
};

} // namespace HDE

#endif // HDE_HTTPRESPONSE_HPP
