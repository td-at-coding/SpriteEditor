cmake_minimum_required(VERSION 3.21)


project(sprite_editor_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(Editor)

add_subdirectory(thirdparty/SFML SYSTEM)


add_executable(tests main.cpp)