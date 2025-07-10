#ifndef SIMPLE_SERVER_HPP
#define SIMPLE_SERVER_HPP

#include "../Sockets/hdelibc-sockets.hpp"
namespace HDE {
    class SimpleServer {
        private:
            ListeningSocket* socket;
            virtual void accepter()=0;
            virtual void handler()=0;
            virtual void responder()=0;

        public:

            // Constructor to create a simple server
            SimpleServer(int domain, int service, int protocol, int port, u_long interface, int bcklg);
            // Destructor to clean up the socket
          

            // Method to start the server
            virtual void launch()=0;

            ListeningSocket* get_socket() const ;
       
    };
}
#endif // SIMPLE_SERVER_HPP