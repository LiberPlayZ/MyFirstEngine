#pragma once

namespace engine {

class Window;

class Renderer {
public:
    Renderer();
    bool Initialize(Window& window);
    void BeginFrame();
    void EndFrame();
    void Shutdown();

private:
    bool m_initialized;
};

}  // namespace engine
