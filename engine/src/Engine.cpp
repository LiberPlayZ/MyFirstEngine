#include "engine/Engine.h"

#include "engine/Input.h"
#include "engine/Log.h"
#include "engine/Renderer.h"
#include "engine/Window.h"

#include <memory>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace engine
{

    Engine::Engine()
        : m_isRunning(false), m_frameCount(0), m_deltaTime(0.0f) {}

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

        m_renderer = std::make_unique<Renderer>();
        if (!m_renderer->Initialize(*m_window))
        {
            LogError("Renderer initialization failed");
            return false;
        }

        m_input = std::make_unique<Input>();
        m_input->Initialize(*m_window);

        m_timer.Reset();

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

        if (m_renderer)
        {
            m_renderer->Shutdown();
            m_renderer.reset();
        }

        m_input.reset();

        m_window.reset();
        LogInfo("Engine shutdown after " + std::to_string(m_frameCount) + " frames");
    }

    void Engine::ProcessFrame()
    {
        ++m_frameCount;
        m_deltaTime = m_timer.Tick();
        LogInfo("Frame " + std::to_string(m_frameCount) + " dt: " + std::to_string(m_deltaTime));

        if (m_window)
        {
            m_window->PollEvents();
        }

        if (m_input && m_input->IsKeyPressed(GLFW_KEY_ESCAPE))
        {
            m_window->Close();
        }
        if (m_input)
        {
            m_input->Update();
        }

        if (m_renderer)
        {
            m_renderer->BeginFrame();
            m_renderer->EndFrame();
        }

        if (m_window)
        {
            m_window->SwapBuffers();
        }
    }

} // namespace engine
