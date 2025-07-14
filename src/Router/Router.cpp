#include "../../include/networking/router/Router.hpp"  // Fixed path

using namespace HDE;

void Router::add_route(const std::string& path, Handler handler) {
    routes[path] = handler;
}

Router::RouteResult Router::handle_request(const HTTPRequest& request) const {
    auto it = routes.find(request.path);
    if (it != routes.end()) {
        return it->second(request);
    }
    return {404,"Not Found", "404 - Resource not found.", "text/plain", {}};
}
