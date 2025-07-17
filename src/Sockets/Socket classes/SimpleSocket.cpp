#include "../../../include/networking/sockets/SimpleSocket.hpp"
#include "../../../include/utils/logger.hpp"
#include <cstring>

HDE::SimpleSocket::SimpleSocket(int domain, int service, int protocol, int port, u_long interface) {
    
    // Initialize the address structure

    address.sin_family = domain;
    address.sin_port = htons(port);
    address.sin_addr.s_addr = htonl(interface);

    // Create the socket
    sock = socket(domain, service, protocol);
    // Check if the socket was created successfully
    test_connection(sock);
    // Bind the socket to the address

}
void HDE::SimpleSocket::test_connection(int to_be_tested) {
    if (to_be_tested < 0) {
        Logger::log("Connection failed: " + std::string(strerror(errno)), Logger::ERROR);
        exit(EXIT_FAILURE);
    }
}
// get the address of the socket
struct sockaddr_in HDE::SimpleSocket::get_address() const {
 
    return address;
}
// get the socket and connection
int HDE::SimpleSocket::get_socket() const {
    return sock;
}
int HDE::SimpleSocket::get_connection() const {
    return connection;
}

//setters
void HDE::SimpleSocket::set_address(const struct sockaddr_in& addr) {
    address = addr;
}       
void HDE::SimpleSocket::set_socket(int s) {
    sock = s;
}
void HDE::SimpleSocket::set_connection(int conn) {
    connection = conn;
}