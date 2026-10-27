project(editor)

include_directories(
    ../include
)

find_package(SFML 3 COMPONENTS Graphics REQUIRED)

add_executable(editor main.cpp)

target_link_libraries(editor PRIVATE SFML::Graphics)
