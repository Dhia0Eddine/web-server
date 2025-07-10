#ifndef LISTENING_SOCKET_HPP
#define LISTENING_SOCKET_HPP

#include "BindingSocket.hpp"

namespace HDE 
{
    class ListeningSocket : public BindingSocket {
         public:
            // Constructor to create a listening socket
            ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int bcklg);
            void start_listening();       
            int connect_to_network(int /*sock*/, struct sockaddr_in /*address*/) override ;
        private:
            int backlog=2;

    };
      

    

}

#endif // LISTENING_SOCKET_HPP