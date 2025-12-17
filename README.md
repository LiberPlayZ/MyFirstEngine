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

### 0. Install dependencies (first time only)

Ubuntu example:

``` bash
sudo apt update
sudo apt install build-essential cmake libglfw3-dev mesa-common-dev
```

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

## 🪟 Window System

The engine now owns a minimal `engine::Window` wrapper implemented with
[GLFW](https://www.glfw.org/). The `Engine` creates a window during
initialization, pumps events every frame, and keeps running until the
user closes the OS window. On pure Wayland sessions, GLFW may try to use
libdecor; either install the GTK plugin (`libdecor-0-plugin-gtk`) or
force GLFW to use X11 via `glfwInitHint(GLFW_PLATFORM,
GLFW_PLATFORM_X11);`. This lays the groundwork for adding an actual
rendering backend later—swap the window wrapper once you add OpenGL,
Vulkan, etc.

Key files:

-   `engine/include/engine/Window.h`
-   `engine/src/Window.cpp`
-   `engine/src/Engine.cpp`

------------------------------------------------------------------------

## 🎨 Renderer

`engine::Renderer` boots an OpenGL context (via GLFW), sets up a viewport
that matches the window size, and clears the screen each frame. This
module is intentionally tiny so you can focus on the integration points:
initialization order (window → renderer), frame boundaries (`BeginFrame`
/ `EndFrame`), and buffer swaps. As you grow the engine, you will expand
this area with shaders, vertex buffers, and scene submission.

Key files:

-   `engine/include/engine/Renderer.h`
-   `engine/src/Renderer.cpp`
-   `engine/src/Engine.cpp`

------------------------------------------------------------------------

## 🧾 Logging

The engine exposes a tiny logging helper in `engine::Log.h`. Use
`engine::LogInfo/LogWarning/LogError` anywhere in engine or game code to
emit timestamped messages. All console output in the sample now goes
through this helper so you can later swap the backend (write to files,
forward to an editor, etc.) without changing call sites.

Example:

``` cpp
#include <engine/Log.h>

void Foo() {
    engine::LogInfo("Something happened");
    engine::LogWarning("Something suspicious happened");
    engine::LogError("Something bad happened");
}
```

The current implementation prints to `std::cout`, but its single
`engine::Log` function is the only place that would need changes when you
upgrade it (e.g., add levels, colors, or log files).

------------------------------------------------------------------------

## 📌 Requirements

-   C++20 compiler\
-   CMake 3.20+\
-   GLFW 3.3 development package (e.g., `sudo apt install libglfw3-dev`
    on Ubuntu)\
-   On modern Ubuntu/Wayland sessions, either install the libdecor GTK
    plugin (`sudo apt install libdecor-0-0 libdecor-0-plugin-gtk`) or
    force GLFW to use X11 (set `GLFW_PLATFORM=X11` or call
    `glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);` before `glfwInit`)\
-   OpenGL headers/libs (e.g., `sudo apt install mesa-common-dev`)\
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
