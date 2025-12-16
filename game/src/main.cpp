#include <engine/Engine.h>

#include <iostream>

int main() {
    std::cout << "[Game] Starting up..." << std::endl;

    engine::Engine engine;
    engine.Run();

    std::cout << "[Game] Exiting." << std::endl;
    return 0;
}
