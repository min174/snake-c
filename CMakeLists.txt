cmake_minimum_required(VERSION 4.0)
project(snake C)

set(CMAKE_C_STANDARD 11)

add_executable(untitled src/main.c
        src/main.c
        src/gameplay.c
        src/menu.c
        include/gameplay.h
        include/menu.h
)

file(COPY data/leaderboard.txt DESTINATION ${CMAKE_BINARY_DIR})