#include "engine/Engine.h"

#include "engine/Input.h"
#include "engine/Log.h"
#include "engine/Renderer.h"
#include "engine/Window.h"

#include <algorithm>
#include <memory>
#include <string>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace engine
{

    Engine::Engine()
        : m_isRunning(false),
          m_frameCount(0),
          m_deltaTime(0.0f),
          m_totalTime(0.0f),
          m_offsetX(0.0f),
          m_offsetY(0.0f),
          m_moveSpeed(0.5f) {}

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
        m_totalTime = 0.0f;
        m_offsetX = 0.0f;
        m_offsetY = 0.0f;

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
        m_totalTime += m_deltaTime;
        if (m_frameCount % 60 == 0)
        {
            LogInfo("Frame " + std::to_string(m_frameCount) + " dt: " + std::to_string(m_deltaTime));
        }

        if (m_window)
        {
            m_window->PollEvents();
        }

        if (m_input)
        {
            if (m_input->IsKeyPressed(GLFW_KEY_ESCAPE))
            {
                m_window->Close();
            }

            const float moveAmount = m_moveSpeed * m_deltaTime;
            if (m_input->IsKeyPressed(GLFW_KEY_A))
            {
                m_offsetX -= moveAmount;
            }
            if (m_input->IsKeyPressed(GLFW_KEY_D))
            {
                m_offsetX += moveAmount;
            }
            if (m_input->IsKeyPressed(GLFW_KEY_W))
            {
                m_offsetY += moveAmount;
            }
            if (m_input->IsKeyPressed(GLFW_KEY_S))
            {
                m_offsetY -= moveAmount;
            }

            m_offsetX = std::clamp(m_offsetX, -0.8f, 0.8f);
            m_offsetY = std::clamp(m_offsetY, -0.8f, 0.8f);

            m_input->Update();
        }

        if (m_renderer)
        {
            m_renderer->BeginFrame();
            m_renderer->Render(m_totalTime, m_offsetX, m_offsetY);
            m_renderer->EndFrame();
        }

        if (m_window)
        {
            m_window->SwapBuffers();
        }
    }

} // namespace engine
