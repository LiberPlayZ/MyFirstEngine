#pragma once

#include <memory>
#include "engine/Input.h"
#include "engine/Renderer.h"
#include "engine/Timer.h"
#include "engine/Window.h"

namespace engine
{

    class Engine
    {
    public:
        Engine();

        void Run();

    private:
        bool Initialize();
        void Shutdown();
        void ProcessFrame();

        bool m_isRunning;
        int m_frameCount;
        std::unique_ptr<Window> m_window;
        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<Input> m_input;
        Timer m_timer;
        float m_deltaTime;
        float m_totalTime;
        float m_offsetX;
        float m_offsetY;
        float m_moveSpeed;
    };

}
