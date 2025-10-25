cmake_minimum_required(VERSION 4.0)
project(snake C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        main.c
)

file(COPY leaderboard.txt DESTINATION ${CMAKE_BINARY_DIR})