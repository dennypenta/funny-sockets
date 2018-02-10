cmake_minimum_required(VERSION 3.9)
project(sockets C)

set(CMAKE_C_STANDARD 11)

add_executable(sockets main.c cmd/init.c cmd/init.h pkg/errors.c pkg/errors.h example_server.c example_server.h)