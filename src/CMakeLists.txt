project(sprite_editor_library)

include_directories(
    ../include
    ../thirdparty/SFML/include
)

add_library(
    sprite_editor_library STATIC 
    sprite/graphics/EditorWindow.cpp
    sprite/graphics/MeasureSection.cpp
    sprite/core/constants.cpp
    sprite/graphics/EditorScreen.cpp
)