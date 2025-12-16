#pragma once

#include <string>

struct GLFWwindow;

namespace engine {

struct WindowConfig {
    int width = 1280;
    int height = 720;
    std::string title = "MyEngine";
};

class Window {
public:
    explicit Window(const WindowConfig& config);
    ~Window();

    bool IsValid() const;
    bool ShouldClose() const;
    void PollEvents();
    void SwapBuffers();

private:
    void Initialize(const WindowConfig& config);
    void Shutdown();

    GLFWwindow* m_handle;
};

}  // namespace engine
