cmake_minimum_required(VERSION 3.16)

project(FirstGameEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add engine and game subdirectories
add_subdirectory(engine)
add_subdirectory(game)

