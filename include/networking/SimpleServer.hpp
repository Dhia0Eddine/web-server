#ifndef SIMPLESERVER_HPP
#define SIMPLESERVER_HPP

#include <memory>
#include "sockets/ListeningSocket.hpp"

namespace HDE {

class SimpleServer {
private:
    std::unique_ptr<ListeningSocket> socket;

public:
    SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bcklg)
        : socket(std::make_unique<ListeningSocket>(domain, service, protocol, port, interface, bcklg)) {}
    
    virtual ~SimpleServer() = default;
    
    ListeningSocket* get_socket() { return socket.get(); }
};

}

#endif