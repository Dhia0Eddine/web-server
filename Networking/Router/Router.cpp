#include "Router.hpp"

using namespace HDE;

void Router::add_route(const std::string& path, Handler handler) {
    routes[path] = handler;
}

std::pair<int, std::string> Router::handle_request(const HTTPRequest& request) const {
    auto it = routes.find(request.path);
    if (it != routes.end()) {
        return it->second(request);
    }
    return {404, "404 - Resource not found."};
}
