#include "engine/Renderer.h"

#include "engine/Log.h"
#include "engine/Window.h"

#include <GL/gl.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace engine {

Renderer::Renderer()
    : m_initialized(false) {}

bool Renderer::Initialize(Window& window) {
    glfwMakeContextCurrent(window.GetNativeHandle());

    glViewport(0, 0, window.GetWidth(), window.GetHeight());
    glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
    m_initialized = true;
    LogInfo("Renderer initialized");
    return true;
}

void Renderer::BeginFrame() {
    if (!m_initialized) {
        return;
    }
    glClear(GL_COLOR_BUFFER_BIT);
}

void Renderer::EndFrame() {
    // Placeholder for future draw submission / buffer management.
}

void Renderer::Shutdown() {
    if (!m_initialized) {
        return;
    }
    m_initialized = false;
    LogInfo("Renderer shutdown");
}

}  // namespace engine
