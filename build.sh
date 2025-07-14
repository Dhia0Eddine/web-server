#!/bin/bash
# filepath: /home/guerfidhia/Desktop/web-server/build.sh

set -e  # Exit on any error

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

# Build type (default: Debug)
BUILD_TYPE=${1:-Debug}

echo -e "${YELLOW}Building HDE Web Server (${BUILD_TYPE})...${NC}"

# Create build directory
if [ ! -d "build" ]; then
    mkdir build
fi

cd build

# Configure with CMake
echo -e "${YELLOW}Configuring with CMake...${NC}"
cmake -DCMAKE_BUILD_TYPE=${BUILD_TYPE} ..

# Build
echo -e "${YELLOW}Building...${NC}"
make -j$(nproc)

echo -e "${GREEN}Build completed successfully!${NC}"
echo -e "${GREEN}Executable: build/web_server${NC}"

# Run tests if available
if [ -f "test_server" ]; then
    echo -e "${YELLOW}Running tests...${NC}"
    ./test_server
fi