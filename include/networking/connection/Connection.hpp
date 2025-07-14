#ifndef HDE_CONNECTION_HPP
#define HDE_CONNECTION_HPP

#include "../../http/HTTPRequest.hpp"
#include "../router/Router.hpp"

#include <netinet/in.h>
#include <string>

namespace HDE {

class Connection {
private:
    int client_socket;
    char buffer[4096];
    HTTPRequest request;
    Router& router;

public:
    Connection(int client_socket, Router& router);
    void process();

private:
    void read_request();
    void handle_request();
    void send_response();
};

} // namespace HDE

#endif // HDE_CONNECTION_HPP
