add_executable(MyGame
    src/main.cpp
)

target_link_libraries(MyGame PRIVATE
    MyEngine
)
