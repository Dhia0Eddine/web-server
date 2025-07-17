# HDE Lightweight C++ Web Server

Welcome! This is **my personal educational project** to **build a real, functioning HTTP web server from scratch in C++** to deeply understand how networking, HTTP parsing, concurrency, and clean system design work.

---

## What is this project?

It's a **tiny but complete web server** that:

- Accepts **HTTP requests** with full **GET, POST, PUT, DELETE** method support.
- Parses the request to extract **method, path, headers, body**.
- Uses a **Router** with method-specific routing and convenient helper methods.
- Builds and sends back **clean HTTP responses** with proper status codes and headers.
- Uses a **ThreadPool** to handle **multiple clients concurrently**.
- Implements **graceful shutdown** with signal handling (SIGINT, SIGTERM).
- Uses **smart pointers** for memory safety and RAII principles.

All using **pure C++ and raw sockets** (no external HTTP libraries), so you learn **exactly what's happening under the hood.**

---

## How does this web server work?

Here's the **life cycle of a client request:**

1. **Socket Creation**:
- We create a TCP socket using `socket()`.
- We bind it to a port (`8080`) and `INADDR_ANY` so it listens on all interfaces.
- We start `listen()` to wait for clients.

2. **Signal Handling**:
- The server registers handlers for `SIGINT` (Ctrl+C) and `SIGTERM` for graceful shutdown.
- When received, the server stops accepting new connections and cleans up resources.

3. **Accepting Connections**:
- When a client connects, the server calls `accept()` to get a **new socket** representing that client.

4. **ThreadPool Handling**:
- Instead of blocking the server for one client, we push the connection to a **ThreadPool**.
- The pool has a fixed number of worker threads, each picking up client connections and handling them in parallel.

5. **Connection Handling**:
- Each connection reads the raw HTTP request into a buffer.
- We parse it into an `HTTPRequest` object with `method`, `path`, `headers`, `body`.

6. **Method-Aware Routing**:
- The `Router` looks at both the **HTTP method** and **path** to decide which handler function to call.
- Support for `GET /users`, `POST /users`, `PUT /users/1`, `DELETE /users/1` with different handlers.
- The handler generates a `RouteResult` with:
  - Status code (`200`, `404`, `201`, etc.)
  - Status text (`OK`, `Created`, `Not Found`)
  - Body content
  - Content-Type
  - Additional headers (if needed)

7. **Responding**:
- We convert the `RouteResult` into a full HTTP response string (`HTTP/1.1 200 OK\r\n...`).
- We send it back to the client with `write()`.
- We close the client socket, freeing resources.

---

## Project Structure

```
web-server/
├── include/              # All .hpp headers, organized clearly
│   ├── networking/
│   │   ├── server/       # SimpleServer, TestServer
│   │   ├── sockets/      # Socket hierarchy
│   │   ├── connection/   # Connection handling
│   │   ├── router/       # HTTP routing with method support
│   │   └── threadpool/   # Thread pool for concurrency
│   ├── http/             # HTTP request/response parsing
│   └── utils/            # Logger and utilities
├── src/                  # All .cpp implementation files
│   ├── Sockets/
│   ├── Server/
│   ├── Connection/
│   ├── Router/
│   └── ThreadPool/
├── build/                # Where build outputs go
├── CMakeLists.txt        # For modern build system
└── README.md
```

---

## New Features & Improvements

### 🔧 **Memory Management & Resource Safety**
- **Smart Pointers**: `SimpleServer` now uses `std::unique_ptr` instead of raw pointers
- **RAII**: Automatic cleanup of sockets and resources
- **Exception Safety**: Proper error handling without memory leaks

### 🛑 **Graceful Shutdown**
- **Signal Handling**: Responds to `SIGINT` (Ctrl+C) and `SIGTERM`
- **Clean Termination**: Stops accepting new connections and finishes processing existing ones
- **Resource Cleanup**: Properly closes sockets and joins threads

### 🌐 **Full HTTP Method Support**
- **GET**: For retrieving resources
- **POST**: For creating new resources
- **PUT**: For updating existing resources
- **DELETE**: For removing resources

### 🎯 **Enhanced Router**
- **Method-Specific Routing**: Different handlers for same path but different methods
- **Convenience Methods**: `router.get()`, `router.post()`, `router.put()`, `router.delete_()`
- **Backward Compatibility**: Still supports old string-based handlers

---

## Building and Running

### 1. Clone and enter the directory:
```bash
git clone https://github.com/Dhia0Eddine/web-server.git
cd web-server
```

### 2. Build with CMake:
```bash
mkdir build
cd build
cmake ..
make
./hde_networking
```

### 3. Graceful shutdown:
```bash
# Press Ctrl+C or send SIGTERM
kill -TERM <process_id>
```

---

## Testing All HTTP Methods

### Using curl:
```bash
# GET requests
curl -X GET http://localhost:8080/hello
curl -X GET http://localhost:8080/users

# POST requests
curl -X POST http://localhost:8080/users \
  -H "Content-Type: application/json" \
  -d '{"name": "Alice", "email": "alice@example.com"}'

curl -X POST http://localhost:8080/login \
  -H "Content-Type: application/json" \
  -d '{"username": "admin", "password": "secret"}'

# PUT requests
curl -X PUT http://localhost:8080/users/1 \
  -H "Content-Type: application/json" \
  -d '{"name": "Bob Updated", "email": "bob@updated.com"}'

# DELETE requests
curl -X DELETE http://localhost:8080/users/1
```

### Using JavaScript (Browser Console):
```javascript
// GET request
fetch('http://localhost:8080/hello')
  .then(response => response.text())
  .then(data => console.log(data));

// POST request
fetch('http://localhost:8080/users', {
  method: 'POST',
  headers: {'Content-Type': 'application/json'},
  body: JSON.stringify({name: 'Alice', email: 'alice@example.com'})
})
.then(response => response.json())
.then(data => console.log(data));
```

---

## What have I learned so far?

- How TCP sockets work practically in C++.  
- How to parse and structure HTTP requests manually.  
- Building a **clean router system** with full HTTP method support.  
- Managing concurrency using a **ThreadPool**.  
- **Memory management** with smart pointers and RAII.
- **Signal handling** for graceful application shutdown.
- Organizing a **real project structure** with `include/`, `src/`, and CMake.  
- Building reusable components like `Router`, `Connection`, and `HTTPResponse`.
- **Modern C++ practices** for safer, more maintainable code.

---

## Next Steps

- [ ] Add comprehensive **unit tests** for all components.
- [ ] Implement **static file serving** (images, CSS, JS).
- [ ] Add **middleware system** for authentication, CORS, logging.
- [ ] Support **HTTP/1.1 keep-alive** connections.
- [ ] Add **configuration file** support.
- [ ] Implement **request/response compression**.
- [ ] Add **performance metrics** and monitoring.
- [ ] Optionally add **TLS (HTTPS)** support.

---

## Why this project?

Because building your own HTTP server **demystifies how the internet actually works**, teaches **modern C++ best practices**, and makes you **deeply comfortable with low-level system programming** while maintaining **clean, maintainable code**.

---

Happy hacking, learning, and exploring!  
– Dhia Eddine
