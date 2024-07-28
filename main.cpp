//
// Created by max on 12.07.24.
//

#include <format>
#include <spdlog/spdlog.h>
#include "Engine.hpp"
#include "Exception.hpp"

int main(int argc, char* argv[]) {
    try {
        auto renderer = sts::Engine::create_renderer(640, 400, "Stellar Salvage");
    } catch(sts::EngineError const& e) {
        spdlog::error(e.what());
    }

    return 0;
}