cmake_minimum_required(VERSION 3.25)
project(test1)

set(CMAKE_CXX_STANDARD 17)

link_libraries(SDL2 SDL2_image SDL2_ttf)

add_executable(test1 main.cpp)
