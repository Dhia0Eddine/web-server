#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include "../Server/HTTPRequest.hpp"
namespace HDE {

class Router {
    public:
        using Handler = std::function<std::pair<int, std::string>(const HTTPRequest&)>; // Handler type for route callbacks

        void add_route(const std::string& path, Handler handler); // Add a route

        std::pair<int, std::string> handle_request(const HTTPRequest& request) const; // Handle incoming requests

    private:
    
        std::unordered_map<std::string, Handler> routes; // Map of routes and their handlers

};

} // namespace HDE

#endif // ROUTER_HPP