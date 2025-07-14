#ifndef CONNECTING_SOCKET_HPP
#define CONNECTING_SOCKET_HPP

#include "SimpleSocket.hpp"

namespace HDE 
{
    class ConnectingSocket : public SimpleSocket {
    public:
        // Constructor to create a connecting socket
        ConnectingSocket(int domain, int service, int protocol, int port, u_long interface);

        // Method to connect to the network
        // This method is pure virtual in SimpleSocket, so it must be implemented here
        // It will connect the socket to the specified address and port
        // Returns the connection status
        // 0 on success, -1 on failure
        // The address parameter is the sockaddr_in structure containing the address and port to connect to
        
        int connect_to_network(int sock, struct sockaddr_in address) override;
    };

}


#endif // CONNECTING_SOCKET_HPP