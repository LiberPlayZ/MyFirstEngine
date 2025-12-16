add_library(MyEngine STATIC
    src/Engine.cpp
    include/engine/Engine.h
)

target_include_directories(MyEngine PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
