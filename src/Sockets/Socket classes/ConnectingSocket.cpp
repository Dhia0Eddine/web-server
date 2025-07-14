#include "../../../include/networking/sockets/ConnectingSocket.hpp"

#include <cstring>

HDE::ConnectingSocket::ConnectingSocket(int domain, int service, int protocol, int port, u_long interface)
    : SimpleSocket(domain, service, protocol, port, interface) {
    // Connect the socket to the address
    set_connection(connect_to_network(get_socket(), get_address()));
    // Check if the connection was successful
    test_connection(get_connection());
}
// Implementation of the connect_to_network method

int HDE::ConnectingSocket::connect_to_network(int sock, struct sockaddr_in address) {
    // Connect the socket to the specified address and port
    if (connect(sock, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Connection failed: " << strerror(errno) << std::endl;
        return -1; // Return -1 on failure
    }
    return 0; // Return 0 on success
}