#ifndef SIMPLE_SOCKET_HPP
#define SIMPLE_SOCKET_HPP

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
namespace HDE {
    class SimpleSocket 
    {
        private:

            struct sockaddr_in address;
            int sock;
            int connection;

        public: 
            SimpleSocket(int domain, int service, int protocol, int port, u_long interface);

            virtual int connect_to_network(int sock, struct sockaddr_in adress )=0;

            void test_connection(int);
            struct sockaddr_in get_address() const;
            int get_socket() const ;
            int get_connection() const;
            
            // setters
            void set_address(const struct sockaddr_in& addr);
            void set_socket(int s) ;
            void set_connection(int conn) ;

    };

}

#endif