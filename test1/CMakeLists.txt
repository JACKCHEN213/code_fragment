cmake_minimum_required(VERSION 3.25)
project(test1)

set(CMAKE_CXX_STANDARD 17)

link_libraries(SDL2 SDL2_image SDL2_ttf)

add_executable(
        test1
        main.cpp
        core/Ball.cpp
        core/Ball.h
        core/Resource.cpp
        core/Resource.h
        core/RectShape.cpp
        core/RectShape.h
        utils/color.h
        core/Cursor.cpp
        core/Cursor.h
        core/DisplayObject.cpp
        core/DisplayObject.h
        core/Slider.cpp core/Slider.h
        core/RectInRect.cpp
        core/RectInRect.h
        core/Eye.cpp
        core/Eye.h
        utils/circle.h
        utils/point.h
)
