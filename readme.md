# Web Server Project

A C++ web server implementation built from scratch using socket programming. This project demonstrates object-oriented design principles and network programming concepts.

## Project Structure

```
web-server/
├── Networking/
│   ├── Sockets/
│   │   ├── Socket classes/
│   │   │   ├── SimpleSocket.hpp/cpp
│   │   │   ├── BindingSocket.hpp/cpp
│   │   │   ├── ConnectingSocket.hpp/cpp
│   │   │   └── ListeningSocket.hpp/cpp
│   │   └── hdelibc-sockets.hpp
│   ├── Server/
│   │   ├── SimpleServer.hpp/cpp
│   │   ├── TestServer.hpp/cpp
│   │   └── test.cpp
│   └── hdelibc-networking.hpp
├── .gitignore
└── README.md
```

## Current Classes and Functions

### Socket Layer

#### `SimpleSocket` (Base Class)
- **Purpose**: Abstract base class for all socket types
- **Functions**:
  - `SimpleSocket(int domain, int service, int protocol, int port, u_long interface)` - Constructor
  - `test_connection(int socket_result)` - Validates socket connection
  - `get_socket()` - Returns socket file descriptor
  - `get_address()` - Returns socket address structure

#### `BindingSocket` (Inherits from SimpleSocket)
- **Purpose**: Handles server-side socket binding to specific addresses
- **Functions**:
  - `BindingSocket(int domain, int service, int protocol, int port, u_long interface)` - Constructor
  - `connect_to_network(int sock, struct sockaddr_in address)` - Binds socket to address

#### `ListeningSocket` (Inherits from BindingSocket)
- **Purpose**: Creates listening sockets for incoming client connections
- **Functions**:
  - `ListeningSocket(int domain, int service, int protocol, int port, u_long interface, int backlog)` - Constructor
  - `start_listening()` - Puts socket in listening mode
  - `connect_to_network()` - Override for listening behavior

#### `ConnectingSocket` (Inherits from SimpleSocket)
- **Purpose**: Handles client-side socket connections
- **Functions**:
  - `ConnectingSocket(int domain, int service, int protocol, int port, u_long interface)` - Constructor
  - `connect_to_network(int sock, struct sockaddr_in address)` - Connects to remote server

### Server Layer

#### `SimpleServer` (Abstract Base Class)
- **Purpose**: Defines interface for all server implementations
- **Functions**:
  - `SimpleServer(int domain, int service, int protocol, int port, u_long interface)` - Constructor
  - `accepter()` - Pure virtual function for accepting connections
  - `handler()` - Pure virtual function for processing requests
  - `responder()` - Pure virtual function for sending responses
  - `launch()` - Pure virtual function for starting server
  - `get_socket()` - Returns pointer to listening socket

#### `TestServer` (Inherits from SimpleServer)
- **Purpose**: Basic HTTP server implementation for testing
- **Functions**:
  - `TestServer()` - Default constructor (creates server on port 8080)
  - `accepter()` - Accepts client connections and reads requests
  - `handler()` - Processes incoming HTTP requests
  - `responder()` - Sends HTTP responses to clients
  - `launch()` - Starts server loop

## Current Features

- Basic socket creation and management
- Server socket binding and listening
- Client connection acceptance
- Basic HTTP request/response handling
- Object-oriented socket abstraction
- Error handling with proper cleanup
- Cross-platform socket compatibility

### Compilation
```bash
cd web-server/Networking/Server
g++ -o test test.cpp TestServer.cpp SimpleServer.cpp \
    ../Sockets/Socket\ classes/SimpleSocket.cpp \
    ../Sockets/Socket\ classes/BindingSocket.cpp \
    ../Sockets/Socket\ classes/ListeningSocket.cpp \
    -I../ -std=c++17
```

### Running
```bash
./test
```

The server will start listening on port 8080. You can test it using:
```bash
curl http://localhost:8080
```

## Future Improvements

### Short-term (Next Release)
- [ ] **Multi-threading Support**: Handle multiple client connections simultaneously
- [ ] **HTTP Parser**: Proper HTTP request parsing (headers, methods, body)

## Architecture Goals

### Design Principles
- **Modularity**: Each component serves a specific purpose
- **Extensibility**: Easy to add new features without breaking existing code
- **Performance**: Optimized for high-throughput scenarios
- **Maintainability**: Clean, well-documented code structure





**Note**: This is an educational project demonstrating socket programming and web server architecture. For production use, consider established frameworks like Flask, Express, or Spring Boot. 