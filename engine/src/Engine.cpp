#include "engine/Engine.h"

#include <chrono>
#include <iostream>
#include <thread>

namespace engine {

Engine::Engine()
    : m_isRunning(false), m_frameCount(0) {}

void Engine::Run() {
    Initialize();

    constexpr int maxFrames = 5;
    while (m_isRunning && m_frameCount < maxFrames) {
        ProcessFrame();
        std::this_thread::sleep_for(std::chrono::milliseconds(16));
    }

    Shutdown();
}

void Engine::Initialize() {
    m_isRunning = true;
    m_frameCount = 0;
    std::cout << "[Engine] Initialized" << std::endl;
}

void Engine::Shutdown() {
    m_isRunning = false;
    std::cout << "[Engine] Shutdown after " << m_frameCount << " frames" << std::endl;
}

void Engine::ProcessFrame() {
    ++m_frameCount;
    std::cout << "[Engine] Frame " << m_frameCount << std::endl;
}

}  // namespace engine
