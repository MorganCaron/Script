cmake_minimum_required(VERSION 3.16)

project(Script)

set(SRCS
	src/main.cpp
	src/hello.cpp
)

set(HEADERS
	src/hello.h
)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wpedantic")

add_executable(Script ${SRCS} ${HEADERS})
