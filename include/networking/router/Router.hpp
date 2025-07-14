#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include "../../http/HTTPRequest.hpp"
namespace HDE {

class Router {
    public:
        struct RouteResult {
            int status_code=200;
            std::string status_text="OK";
            std::string body="";
            std::string content_type="text/plain";
            std::unordered_map<std::string, std::string> additional_headers={};
        };

        using Handler = std::function<RouteResult(const HTTPRequest&)>; // Handler type for route callbacks

        void add_route(const std::string& path, Handler handler); // Add a route

        RouteResult handle_request(const HTTPRequest& request)const;


        // New method to remove a route
        bool remove_route(const std::string& path);

        // New method to check if a route exists
        bool route_exists(const std::string& path) const;

    private:
        std::unordered_map<std::string, Handler> routes; // Map of routes and their handlers

};

} // namespace HDE

#endif // ROUTER_HPP