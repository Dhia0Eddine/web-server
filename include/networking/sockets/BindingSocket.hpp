#ifndef BINDING_SOCKET_HPP
#define BINDING_SOCKET_HPP

#include "SimpleSocket.hpp"
namespace HDE 
{
    class BindingSocket : public SimpleSocket {
    public:
        // Constructor to create a binding socket
        BindingSocket(int domain, int service, int protocol, int port, u_long interface);

        // Method to connect to the network
        // This method is pure virtual in SimpleSocket, so it must be implemented here
        // It will bind the socket to the specified address and port
        // Returns the connection status
        // 0 on success, -1 on failure
        // The address parameter is the sockaddr_in structure containing the address and port to bind to
        
        int connect_to_network(int sock, struct sockaddr_in address) override;
    };

}
#endif // BINDING_SOCKET_HPP