#include <catch2/catch_all.hpp>
#include "../../include/http/HTTPRequest.hpp"

using namespace HDE;

TEST_CASE("HTTPRequest parses simple GET request", "[HTTPRequest]") {
    std::string raw_request = "GET /hello HTTP/1.1\r\nHost: localhost\r\n\r\n";
    auto req = HTTPRequest::parse(raw_request);

    REQUIRE(req.method == "GET");
    REQUIRE(req.path == "/hello");
    REQUIRE(req.http_version == "HTTP/1.1");
    REQUIRE(req.headers["Host"] == "localhost");
}
