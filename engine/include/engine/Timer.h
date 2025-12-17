#pragma once

#include <chrono>

namespace engine {

class Timer {
public:
    Timer();

    void Reset();
    float Tick();
    float DeltaTime() const { return m_deltaTime; }

private:
    using clock = std::chrono::steady_clock;
    clock::time_point m_lastTime;
    float m_deltaTime;
};

}  // namespace engine
