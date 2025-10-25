cmake_minimum_required(VERSION 4.0)
project(snake C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled main.c
        main.c
        gameplay.c
        menu.c
        gameplay.h
        menu.h
)

file(COPY leaderboard.txt DESTINATION ${CMAKE_BINARY_DIR})