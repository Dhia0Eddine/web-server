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
    src/utils/Config.cpp
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

# Testing setup
option(BUILD_TESTS "Build the tests" ON)

if(BUILD_TESTS)
    # Try to find Catch2
    find_package(Catch2 3 QUIET)
    
    if(NOT Catch2_FOUND)
        # If Catch2 is not found, try to use FetchContent to download it
        include(FetchContent)
        FetchContent_Declare(
            Catch2
            GIT_REPOSITORY https://github.com/catchorg/Catch2.git
            GIT_TAG        v3.4.0 # or any tag you want
        )
        FetchContent_MakeAvailable(Catch2)
        
        # Add Catch2 to the module path
        list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
    endif()

    # Enable testing
    enable_testing()

    # Add test executable
    file(GLOB TEST_SOURCES "tests/unit/*.cpp" "tests/integration/*.cpp")
    
    if(TEST_SOURCES)
        add_executable(run_tests ${TEST_SOURCES})
        target_link_libraries(run_tests PRIVATE hde_networking Catch2::Catch2WithMain Threads::Threads)
        target_include_directories(run_tests PRIVATE include tests)
        target_compile_features(run_tests PRIVATE cxx_std_17)

        # Discover and add tests
        if(TARGET Catch2::Catch2)
            include(Catch)
            catch_discover_tests(run_tests)
        else()
            add_test(NAME AllTests COMMAND run_tests)
        endif()
    else()
        message(WARNING "No test sources found in tests/ directory")
    endif()
endif()

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