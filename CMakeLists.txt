cmake_minimum_required(VERSION 3.10)
project(b64 C)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Add the executable
add_executable(b64 src/main.c)
