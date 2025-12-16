# MyEngine -- C++ Game Engine (Work in Progress)

MyEngine is a custom C++ game engine built from scratch as a learning
and exploration project.\
The goal is to understand the fundamental architecture of a real engine,
including modules such as:

-   Window & Game Loop\
-   Rendering (OpenGL/Vulkan)\
-   Input System\
-   Math Module\
-   Resource Management\
-   Scene / ECS\
-   Tools & Utilities

This project is built using **modern CMake** and structured in a
scalable, modular way.

------------------------------------------------------------------------

## 📁 Project Structure

    MyEngine/
     ├── engine/
     │     ├── include/        # Public headers (engine API)
     │     ├── src/            # Engine implementation
     │     └── CMakeLists.txt  # Engine build rules
     ├── game/
     │     ├── src/            # Game/application entry point
     │     └── CMakeLists.txt  # Game build rules
     ├── CMakeLists.txt         # Root CMake setup
     ├── README.md
     └── .gitignore

More modules (core, renderer, math, etc.) will be added as the engine
expands.

------------------------------------------------------------------------

## 🔧 Building the Project

### 1. Configure CMake

``` bash
cmake -S . -B build
```

### 2. Build (and re-build)

``` bash
cmake --build build
```

### 3. Run the example game

``` bash
./build/game/MyGame
```

This sequence builds the `MyEngine` static library and links the
`MyGame` executable against it so you can immediately see console output
from both layers.

------------------------------------------------------------------------

## 📌 Requirements

-   C++20 compiler\
-   CMake 3.20+\
-   Linux (Ubuntu) --- primary development environment\
-   Optional: VSCode or CLion

------------------------------------------------------------------------

## 🚧 Current Status

The project is in **Step 1: CMake and project structure setup**.

Next steps (coming soon):

-   Step 2: Create a Window with GLFW\
-   Step 3: Engine Loop\
-   Step 4: Logging System\
-   Step 5: Math Module (GLM)

------------------------------------------------------------------------

## 📜 License

(We will add license information later.)

------------------------------------------------------------------------

## 🤝 Contributing

This project is personal-study oriented, but structured for future
collaboration.

------------------------------------------------------------------------

## 📅 Development Plan

This project follows a clear roadmap:

1.  Engine bootstrap (CMake, structure)\
2.  Windowing + Game Loop\
3.  Rendering backend\
4.  Input system\
5.  ECS\
6.  Tools / Editors

Each step will be documented in detail as the project evolves.

------------------------------------------------------------------------
