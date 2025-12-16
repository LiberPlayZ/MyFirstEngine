#include "engine/Engine.h"

#include "engine/Log.h"
#include "engine/Window.h"

#include <chrono>
#include <memory>
#include <string>
#include <thread>

namespace engine
{

    Engine::Engine()
        : m_isRunning(false), m_frameCount(0) {}

    void Engine::Run()
    {
        if (!Initialize())
        {
            LogError("Engine failed to initialize");
            return;
        }

        while (m_isRunning && m_window && !m_window->ShouldClose())
        {
            ProcessFrame();
        }

        Shutdown();
    }

    bool Engine::Initialize()
    {
        m_window = std::make_unique<Window>(WindowConfig{});
        if (!m_window->IsValid())
        {
            LogError("Window initialization failed");
            return false;
        }

        m_isRunning = true;
        m_frameCount = 0;
        LogInfo("Engine initialized");
        return true;
    }

    void Engine::Shutdown()
    {
        if (!m_isRunning)
        {
            return;
        }

        m_isRunning = false;
        m_window.reset();
        LogInfo("Engine shutdown after " + std::to_string(m_frameCount) + " frames");
    }

    void Engine::ProcessFrame()
    {
        ++m_frameCount;
        LogInfo("Processing frame " + std::to_string(m_frameCount));

        if (m_window)
        {
            m_window->PollEvents();
            m_window->SwapBuffers();
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

} // namespace engine
