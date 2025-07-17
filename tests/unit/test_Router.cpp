#include <catch2/catch_all.hpp>
#include "../../include/networking/router/Router.hpp"

using namespace HDE;

TEST_CASE("Router returns correct RouteResult", "[Router]") {
    Router router;

    router.add_route("/test", [](const HTTPRequest&) {
        return Router::RouteResult{200, "Test OK","body", "text/plain", {}};
    });

    HTTPRequest req;
    req.path = "/test";

    auto result = router.handle_request(req);

    REQUIRE(result.status_code == 200);
    REQUIRE(result.body == "body");
    REQUIRE(result.content_type == "text/plain");
}
