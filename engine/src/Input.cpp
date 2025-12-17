#include "engine/Input.h"

#include "engine/Window.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace engine {

Input::Input()
    : m_window(nullptr) {}

void Input::Initialize(Window& window) {
    m_window = window.GetNativeHandle();
}

void Input::Update() {
    // Placeholder for future state accumulation (mouse delta, text input, etc.).
}

bool Input::IsKeyPressed(int key) const {
    if (!m_window) {
        return false;
    }
    return glfwGetKey(m_window, key) == GLFW_PRESS;

}

}  // namespace engine
