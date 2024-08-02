//
// Created by max on 12.07.24.
//

#include <format>
#include <spdlog/spdlog.h>
#include "Engine.hpp"
#include "Exception.hpp"

using namespace std::chrono_literals;

int main(int argc, char* argv[]) {
    try {
        auto const renderer = sts::Engine::create_renderer(640, 400, "Stellar Salvage");
        if(!renderer) {
            spdlog::error("could not initialize renderer");
            return -1;
        }
        bool running = true;
        sts::Rect constexpr rect{32,32,100,100};

        auto const start = std::chrono::system_clock::now();

        while(sts::Engine::is_window_open()) {
            if(std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()-start) > 5000ms) {
                running = false;
            }
            renderer->clear();
            renderer->draw_filled_rect(rect, sts::Color::CYAN);
            renderer->draw_filled_circle(0, 0, 32, sts::Color::PLUM);
            renderer->present();

            std::this_thread::sleep_for(1000ms/60);
        }
    } catch(sts::EngineError const& e) {
        spdlog::error(e.what());
    }

    return 0;
}