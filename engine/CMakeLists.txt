add_library(MyEngine STATIC
    src/Engine.cpp
    src/Log.cpp
    include/engine/Engine.h
    include/engine/Log.h
)

target_include_directories(MyEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
