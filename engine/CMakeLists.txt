find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)

add_library(MyEngine STATIC
    src/Engine.cpp
    src/Input.cpp
    src/Log.cpp
    src/Renderer.cpp
    src/Timer.cpp
    src/Window.cpp

)

target_include_directories(MyEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(MyEngine
    PUBLIC
        glfw
        OpenGL::GL
)
