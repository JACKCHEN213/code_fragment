cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME demo1)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 17)

aux_source_directory(. SRC_LIST)

add_executable(${PROJECT_NAME} ${SRC_LIST} main.cpp)

find_package(PkgConfig REQUIRED)

pkg_check_modules(SDL2 REQUIRED sdl2)
pkg_check_modules(SDL2_IMG REQUIRED SDL2_image)
pkg_check_modules(SDL2_TTF REQUIRED SDL2_ttf)
pkg_check_modules(SDL2_MIX REQUIRED SDL2_mixer)

include_directories (
        ${SDL2_INCLUDE_DIRS}
        ${SDL2_IMG_INCLUDE_DIRS}
        ${SDL2_TTF_INCLUDE_DIRS}
        ${SDL2_MIX_INCLUDE_DIRS}
)

link_directories (
        ${SDL2_LIBRARY_DIRS}
        ${SDL2_IMG_LIBRARY_DIRS}
        ${SDL2_TTF_LIBRARY_DIRS}
        ${SDL2_MIX_LIBRARY_DIRS}
)

target_link_libraries (
        ${PROJECT_NAME}
        ${SDL2_LIBRARIES}
        ${SDL2_IMG_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIX_LIBRARIES}
)
