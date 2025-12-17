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
    void Close();
    GLFWwindow* GetNativeHandle() const;
    int GetWidth() const { return m_width; }
    int GetHeight() const { return m_height; }

private:
    void Initialize(const WindowConfig& config);
    void Shutdown();

    GLFWwindow* m_handle;
    int m_width;
    int m_height;
};

}  // namespace engine
