# HDE Lightweight C++ Web Server

Welcome! This is **my personal educational project** to **build a real, functioning HTTP web server from scratch in C++** to deeply understand how networking, HTTP parsing, concurrency, and clean system design work.

---

## What is this project?

It’s a **tiny but complete web server** that:

- Accepts **HTTP requests** (like when you use `curl` or your browser).
- Parses the request to extract **method, path, headers, body**.
- Uses a **Router** to map paths like `/hello` to your handler code.
- Builds and sends back **clean HTTP responses** to the client.
- Uses a **ThreadPool** to handle **multiple clients concurrently**.

All using **pure C++ and raw sockets** (no external HTTP libraries), so you learn **exactly what’s happening under the hood.**

---

## How does this web server work?

Here’s the **life cycle of a client request:**

1. **Socket Creation**:
- We create a TCP socket using `socket()`.
- We bind it to a port (`8080`) and `INADDR_ANY` so it listens on all interfaces.
- We start `listen()` to wait for clients.

2. **Accepting Connections**:
- When a client connects, the server calls `accept()` to get a **new socket** representing that client.

3. **ThreadPool Handling**:
- Instead of blocking the server for one client, we push the connection to a **ThreadPool**.
- The pool has a fixed number of worker threads, each picking up client connections and handling them in parallel.

4. **Connection Handling**:
- Each connection reads the raw HTTP request into a buffer.
- We parse it into an `HTTPRequest` object with `method`, `path`, `headers`, `body`.

5. **Routing**:
- The `Router` looks at the `path` and decides which handler function to call (e.g., `/hello`, `/time`).
- The handler generates a `RouteResult` with:
  - Status code (`200`, `404`, etc.)
  - Body
  - Content-Type
  - Additional headers (if needed)

6. **Responding**:
- We convert the `RouteResult` into a full HTTP response string (`HTTP/1.1 200 OK\r\n...`).
- We send it back to the client with `write()`.
- We close the client socket, freeing resources.

---

## Project Structure

```
web-server/
├── include/              # All .hpp headers, organized clearly
│   ├── networking/
│   └── http/
├── src/                  # All .cpp implementation files
│   ├── sockets/
│   ├── server/
│   ├── connection/
│   ├── router/
│   └── threadpool/
├── build/                # Where build outputs go
├── CMakeLists.txt        # For modern build system
└── README.md
```

---

## Why do we use CMake?

- **CMake is a cross-platform build system** that generates platform-specific build files (Makefiles, Ninja, Visual Studio solutions, etc.).
- It **automates dependency handling** between files, avoiding manual compilation headaches.
- It **scales well as your project grows** with more files, tests, and dependencies.
- CMake allows **clean out-of-source builds**, keeping your `build/` folder separate from your `src/`.

---

## Building and Running

### 1. Clone and enter the directory:
```bash
git clone https://github.com/yourusername/web-server.git
cd web-server
```

### 2. Build with CMake:
```bash
mkdir build
cd build
cmake ..
make
./web_server
```

---

## Testing

Open a new terminal:

```bash
curl http://localhost:8080/hello
curl http://localhost:8080/time
curl http://localhost:8080/json
```

You will see parsed requests and server responses printed to your server terminal.

---

## What have I learned so far?

- How TCP sockets work practically in C++.  
- How to parse and structure HTTP requests manually.  
- Building a **clean router system** for handling endpoints.  
- Managing concurrency using a **ThreadPool**.  
- Organizing a **real project structure** with `include/`, `src/`, and CMake.  
- Building reusable components like `Router`, `Connection`, and `HTTPResponse`.

---

## Next Steps

- [ ] Add structured **logging** with colored output for clarity.
- [ ] Add **unit tests** for HTTP parsing and router logic.
- [ ] Extend routing to handle **HTTP methods (GET, POST, etc.)**.
- [ ] Add support for **static file serving** (images, CSS, JS).
- [ ] Add **persistent connection (keep-alive)** support.
- [ ] Optionally add **TLS (HTTPS)** in the future.

---

## Why this project?

Because building your own HTTP server **demystifies how the internet actually works**, and makes you **deeply comfortable with low-level system programming in C++**.

---

Happy hacking, learning, and exploring!  
– Dhia Eddine
