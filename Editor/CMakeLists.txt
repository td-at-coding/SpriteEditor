project(editor)

include_directories(
    ../include
)


add_executable(editor main.cpp)

target_compile_definitions(editor PRIVATE 
    SOURCE_DIR="${CMAKE_SOURCE_DIR}"
)

target_link_libraries(editor PRIVATE SFML::Graphics)
