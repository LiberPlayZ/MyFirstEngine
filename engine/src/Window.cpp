#include "engine/Window.h"

#include "engine/Log.h"

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace engine
{

    namespace
    {
        bool g_glfwInitialized = false;
    }

    Window::Window(const WindowConfig &config)
        : m_handle(nullptr),
          m_width(config.width),
          m_height(config.height)
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
            // Force X11 backend on Wayland systems to avoid libdecor crashes.
            glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

            if (!glfwInit())
            {
                LogError("Failed to initialize GLFW");
                return;
            }
            g_glfwInitialized = true;
        }

        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #if defined(__APPLE__)
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
    #endif

        m_handle = glfwCreateWindow(config.width, config.height, config.title.c_str(), nullptr, nullptr);

        if (!m_handle)
        {
            LogError("Failed to create GLFW window");
        }
        else
        {
            LogInfo("Window created: " + config.title);
            glfwMakeContextCurrent(m_handle);
            glfwSwapInterval(1);
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

    GLFWwindow *Window::GetNativeHandle() const
    {
        return m_handle;
    }

} // namespace engine
