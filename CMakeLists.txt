cmake_minimum_required(VERSION 3.16)
project(reloop LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include headers
include_directories(src/include)

# Sources
add_executable(reloop
    src/main.cpp
)

# Install the binary to /usr/local/bin by default
install(TARGETS reloop DESTINATION bin)
