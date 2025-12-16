#pragma once

namespace engine {

class Engine {
public:
    Engine();

    void Run();

private:
    void Initialize();
    void Shutdown();
    void ProcessFrame();

    bool m_isRunning;
    int m_frameCount;
};

}
