#include "engine/Engine.h"

#include "engine/Log.h"

#include <chrono>
#include <string>
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
    LogInfo("Engine initialized");
}

void Engine::Shutdown() {
    m_isRunning = false;
    LogInfo("Engine shutdown after " + std::to_string(m_frameCount) + " frames");
}

void Engine::ProcessFrame() {
    ++m_frameCount;
    LogInfo("Processing frame " + std::to_string(m_frameCount));
}

}  // namespace engine
