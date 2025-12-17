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

```
first-game-engine/
├── CMakeLists.txt
├── engine/
│   ├── CMakeLists.txt
│   ├── include/engine/
│   │   ├── Engine.h        # Engine facade
│   │   ├── Input.h         # Keyboard wrapper (GLFW)
│   │   ├── Log.h           # Logging helpers
│   │   ├── Renderer.h      # OpenGL renderer
│   │   ├── Timer.h         # High-resolution timer
│   │   └── Window.h        # OS window abstraction
│   └── src/
│       ├── Engine.cpp
│       ├── Input.cpp
│       ├── Log.cpp
│       ├── Renderer.cpp
│       ├── Timer.cpp
│       └── Window.cpp
├── game/
│   ├── CMakeLists.txt
│   └── src/main.cpp        # Demo entry point
├── resources/              # Future assets, configs, shaders
└── README.md
```

Everything under `engine/` builds into the `MyEngine` static library;
`game/` links that library and serves as the sandbox for testing new
engine features.

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

What you should see:

-   A window (1280x720) with a dark background
-   A small triangle whose green channel pulses over time
-   `W/A/S/D` moves the triangle, `Esc` closes the window
-   Console logs every ~60 frames showing the measured delta time

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
that matches the window size, and now draws a tiny triangle with a
time-varying color. The module shows the full shader/VAO/VBO pipeline so
you can see how render state is created, uniform values are updated, and
draw calls are submitted each frame. All OpenGL entry points are loaded
on-demand via `glfwGetProcAddress`, so the code mirrors what larger
engines do before delegating to a graphics abstraction layer.

Key files:

-   `engine/include/engine/Renderer.h`
-   `engine/src/Renderer.cpp`
-   `engine/src/Engine.cpp`

------------------------------------------------------------------------

## ⏱️ Timing & Input

`engine::Timer` tracks high-resolution delta time so each frame knows how
much real time has elapsed. The engine logs this delta periodically
(useful for spotting spikes) and feeds accumulated time into the renderer
to animate colors. `engine::Input` wraps keyboard state via GLFW; the
sample maps `W/A/S/D` to move the triangle and `Esc` to close the window.
As you expand, wire mouse movement, text input, or action-mapping tables
through the same module.

Key files:

-   `engine/include/engine/Timer.h`
-   `engine/src/Timer.cpp`
-   `engine/include/engine/Input.h`
-   `engine/src/Input.cpp`
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

✔️ CMake project layout\
✔️ Engine facade with window, renderer, timer, input, and logging\
✔️ OpenGL triangle demo w/ color animation and keyboard movement\
⬜ Platform abstraction (GLFW + other backends)\
⬜ Math module (GLM or custom)\
⬜ Scene graph / ECS\
⬜ Resource management and tooling

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

1.  Engine bootstrap (CMake, structure) ✅\
2.  Windowing + Game Loop ✅\
3.  Rendering backend (in progress, OpenGL triangle demo)\
4.  Input system ✅ (keyboard prototype)\
5.  Math / camera / scene graph\
6.  Asset pipeline, ECS, tools/editors

Each step will be documented in detail as the project evolves. If you’re
following along, try implementing the next subsystem (e.g., a camera
class, shader hot-reload, or a logging UI) and plug it into the
structure shown above.

------------------------------------------------------------------------
