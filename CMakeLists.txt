cmake_minimum_required(VERSION 3.16)
project(HDE_WebServer VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find required packages
find_package(Threads REQUIRED)

# Source files
file(GLOB SOCKET_SOURCES "src/Sockets/Socket classes/*.cpp")

set(SERVER_SOURCES
    src/Server/SimpleServer.cpp
    src/Server/TestServer.cpp
    src/Server/HTTPRequest.cpp
    src/Server/HTTPResponse.cpp
)

set(NETWORKING_SOURCES
    src/Connection/Connection.cpp
    src/Router/Router.cpp
    src/ThreadPool/ThreadPool.cpp
)

set(ALL_SOURCES
    ${SOCKET_SOURCES}
    ${SERVER_SOURCES}
    ${NETWORKING_SOURCES}
)

# Create static library for reusable components
add_library(hde_networking STATIC ${ALL_SOURCES})
target_link_libraries(hde_networking Threads::Threads)

# Main executable (test.cpp is in root directory)
add_executable(web_server test.cpp)
target_link_libraries(web_server hde_networking Threads::Threads)

# Install targets
install(TARGETS web_server
    RUNTIME DESTINATION bin
)

install(DIRECTORY include/
    DESTINATION include
    FILES_MATCHING PATTERN "*.hpp"
)

# CPack configuration for packaging
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)