#include "../../include/networking/router/Router.hpp"

using namespace HDE;

void Router::add_route(const std::string& method, const std::string& path, Handler handler) {
    routes[method][path] = handler;
}

void Router::add_route(const std::string& path, Handler handler) {
    add_route("GET", path, handler);
}

Router::RouteResult Router::handle_request(const HTTPRequest& request) const {
    // First try RouteHandler routes
    auto method_it = route_handlers.find(request.method);
    if (method_it != route_handlers.end()) {
        auto path_it = method_it->second.find(request.path);
        if (path_it != method_it->second.end()) {
            return path_it->second(request);
        }
    }
    
    // Then try string Handler routes
    auto str_method_it = routes.find(request.method);
    if (str_method_it != routes.end()) {
        auto str_path_it = str_method_it->second.find(request.path);
        if (str_path_it != str_method_it->second.end()) {
            return RouteResult(true, str_path_it->second(request));
        }
    }
    
    return RouteResult(false, "404 Not Found");
}
