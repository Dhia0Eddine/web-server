#ifndef ROUTER_HPP
#define ROUTER_HPP

#include <unordered_map>
#include <string>
#include <functional>
#include "../../http/HTTPRequest.hpp"

namespace HDE {

class Router {
public:
    struct RouteResult {
        bool found;
        int status_code;          // Moved before body to fix initialization order
        std::string status_text;
        std::string response;
        std::string body;
        std::string content_type;
        std::unordered_map<std::string, std::string> headers;
        std::unordered_map<std::string, std::string> additional_headers;
        
        // Constructor for backward compatibility (2 arguments)
        RouteResult(bool f, const std::string& r) 
            : found(f), status_code(200), status_text("OK"), response(r), body(r), content_type("text/plain") {}
        
        // Constructor for full HTTP response (5 arguments)
        RouteResult(int code, const std::string& msg, const std::string& body_content, 
                   const std::string& type, const std::unordered_map<std::string, std::string>& hdrs)
            : found(true), status_code(code), status_text(msg), response(body_content), 
              body(body_content), content_type(type), headers(hdrs), additional_headers(hdrs) {}
    };

    using Handler = std::function<std::string(const HTTPRequest&)>;
    using RouteHandler = std::function<RouteResult(const HTTPRequest&)>;
    
    // New 3-argument method with RouteHandler
    void add_route(const std::string& method, const std::string& path, RouteHandler handler) {
        route_handlers[method][path] = handler;
    }
    
    // Backward compatibility: 2-argument method with RouteHandler (defaults to GET)
    void add_route(const std::string& path, RouteHandler handler) {
        add_route("GET", path, handler);
    }
    
    // String handler methods - remove inline implementation to avoid redefinition
    void add_route(const std::string& method, const std::string& path, Handler handler);
    void add_route(const std::string& path, Handler handler);
    
    // Convenience methods for common HTTP methods
    void get(const std::string& path, RouteHandler handler) { 
        add_route("GET", path, handler); 
    }
    
    void post(const std::string& path, RouteHandler handler) { 
        add_route("POST", path, handler); 
    }
    
    void put(const std::string& path, RouteHandler handler) { 
        add_route("PUT", path, handler); 
    }
    
    void delete_(const std::string& path, RouteHandler handler) { 
        add_route("DELETE", path, handler); 
    }
    
    // Remove const to match implementation
    RouteResult handle_request(const HTTPRequest& request) const;

private:
    std::unordered_map<std::string, std::unordered_map<std::string, Handler>> routes;
    std::unordered_map<std::string, std::unordered_map<std::string, RouteHandler>> route_handlers;
};

}

#endif