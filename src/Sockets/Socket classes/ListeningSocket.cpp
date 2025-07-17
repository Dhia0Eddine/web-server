#include "../../../include/networking/sockets/ListeningSocket.hpp"
#include "../../../include/utils/logger.hpp"
#include <cstring>

HDE::ListeningSocket::ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bcklg)
    : BindingSocket(domain, service, protocol, port, interface), backlog(bcklg) {
    // Set the socket to listen for incoming connections
    start_listening();
}

void HDE::ListeningSocket::start_listening(){
    // Start listening on the socket with the specified backlog
    if (listen(get_socket(), backlog) < 0) {
        Logger::log("Listening failed: " + std::string(strerror(errno)), Logger::ERROR);
        exit(EXIT_FAILURE); // Exit if listening fails
    }
    Logger::log("Socket is now listening with a backlog of " + std::to_string(backlog), Logger::INFO);
}

int HDE::ListeningSocket::connect_to_network(int /*sock*/, struct sockaddr_in /*address*/) {
    // This method is not used in ListeningSocket, so we can leave it empty or throw an error
    throw std::runtime_error("ListeningSocket does not support connect_to_network.");
}