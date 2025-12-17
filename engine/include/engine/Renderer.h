#pragma once

namespace engine {

class Window;

class Renderer {
public:
    Renderer();
    bool Initialize(Window& window);
    void BeginFrame();
    void Render(float totalTime, float offsetX, float offsetY);
    void EndFrame();
    void Shutdown();

private:
    bool m_initialized;
    unsigned int m_vao;
    unsigned int m_vbo;
    unsigned int m_program;
    int m_timeUniform;
    int m_offsetUniform;
};

}  // namespace engine
