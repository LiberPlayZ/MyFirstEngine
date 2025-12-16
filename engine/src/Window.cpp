#include "engine/Window.h"

#include "engine/Log.h"

#include <GLFW/glfw3.h>

namespace engine
{

    namespace
    {
        bool g_glfwInitialized = false;
    }

    Window::Window(const WindowConfig &config)
        : m_handle(nullptr)
    {
        Initialize(config);
    }

    Window::~Window()
    {
        Shutdown();
    }

    void Window::Initialize(const WindowConfig &config)
    {
        if (!g_glfwInitialized)
        {
            if (!glfwInit())
            {
                LogError("Failed to initialize GLFW");
                return;
            }
            g_glfwInitialized = true;
        }

        glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);
        m_handle = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);

        if (!m_handle)
        {
            LogError("Failed to create GLFW window");
        }
        else
        {
            LogInfo("Window created: " + config.title);
        }
    }

    void Window::Shutdown()
    {
        if (m_handle)
        {
            glfwDestroyWindow(m_handle);
            m_handle = nullptr;
            LogInfo("Window destroyed");
        }

        if (g_glfwInitialized)
        {
            glfwTerminate();
            g_glfwInitialized = false;
        }
    }

    bool Window::IsValid() const
    {
        return m_handle != nullptr;
    }

    bool Window::ShouldClose() const
    {
        return m_handle == nullptr || glfwWindowShouldClose(m_handle);
    }

    void Window::PollEvents()
    {
        glfwPollEvents();
    }

    void Window::SwapBuffers()
    {
        if (m_handle)
        {
            glfwSwapBuffers(m_handle);
        }
    }

} // namespace engine
