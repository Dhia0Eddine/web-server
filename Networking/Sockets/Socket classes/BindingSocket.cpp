#include "BindingSocket.hpp"
#include <cstring>
HDE::BindingSocket::BindingSocket(int domain, int service, int protocol, int port, u_long interface)
    : SimpleSocket(domain, service, protocol, port, interface) {
    // Bind the socket to the address
    set_connection(connect_to_network(get_socket(), get_address()));
    // Check if the connection was successful
    test_connection(get_connection());
    
}
// Implementation of the connect_to_network method
// This method binds the socket to the specified address and port
// Returns 0 on success, -1 on failure
// The address parameter is the sockaddr_in structure containing the address and port to bind to

int HDE::BindingSocket::connect_to_network(int sock, struct sockaddr_in address) {
    // Bind the socket to the specified address and port
    if (bind(sock, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Binding failed: " << strerror(errno) << std::endl;
        return -1; // Return -1 on failure
    }
    return 0; // Return 0 on success
}