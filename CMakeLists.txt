cmake_minimum_required(VERSION 3.9)
project(sockets C)

set(CMAKE_C_STANDARD 11)

add_executable(sockets main.c cmd/app/init.c cmd/app/init.h pkg/errors.c pkg/errors.h)