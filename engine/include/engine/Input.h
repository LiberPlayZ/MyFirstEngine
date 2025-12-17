#pragma once

struct GLFWwindow;

namespace engine {

class Window;

class Input {
public:
    Input();

    void Initialize(Window& window);
    void Update();
    bool IsKeyPressed(int key) const;

private:
    GLFWwindow* m_window;
};

}  // namespace engine
