find_package(glfw3 3.3 REQUIRED)

add_library(MyEngine STATIC
    src/Engine.cpp
    src/Log.cpp
    src/Window.cpp
    include/engine/Engine.h
    include/engine/Log.h
    include/engine/Window.h
)

target_include_directories(MyEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MyEngine
    PUBLIC
        glfw
)
