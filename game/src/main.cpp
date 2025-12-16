#include <engine/Engine.h>
#include <engine/Log.h>

int main() {
    engine::LogInfo("Game starting up...");
    engine::Engine engine;
    engine.Run();
    engine::LogInfo("Game exiting.");
    return 0;
}
