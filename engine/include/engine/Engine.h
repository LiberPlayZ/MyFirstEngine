#pragma once

#include <memory>
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
    };

}
