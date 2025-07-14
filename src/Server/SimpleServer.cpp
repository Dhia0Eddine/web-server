#include "../../include/networking/server/SimpleServer.hpp"

HDE::SimpleServer::SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bcklg) {
    // Create a listening socket for the server
    socket = new ListeningSocket(domain, service, protocol, port, interface, bcklg);
}

HDE::ListeningSocket* HDE::SimpleServer::get_socket() const {
    return socket;
}

// Destructor to clean up the socket