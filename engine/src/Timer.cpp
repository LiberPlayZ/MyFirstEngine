#include "engine/Timer.h"

namespace engine {

Timer::Timer()
    : m_lastTime(clock::now()), m_deltaTime(0.0f) {}

void Timer::Reset() {
    m_lastTime = clock::now();
    m_deltaTime = 0.0f;
}

float Timer::Tick() {
    const auto current = clock::now();
    m_deltaTime = std::chrono::duration<float>(current - m_lastTime).count();
    m_lastTime = current;
    return m_deltaTime;
}

}  // namespace engine
