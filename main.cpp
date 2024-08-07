//
// Created by max on 12.07.24.
//

#include <format>
#include <spdlog/spdlog.h>
#include "Engine.hpp"
#include "Exception.hpp"

using namespace std::chrono_literals;

sts::Rect player{32, 32, 200, 200};
sts::Rect delta{};

void handle_events() {
    delta.x = 0;
    delta.y = 0;
    if(sts::Engine::is_key_pressed(sts::KeyCode::S)) {
        delta.x = -5;
    }
    if(sts::Engine::is_key_pressed(sts::KeyCode::F)) {
        delta.x = 5;
    }
    if(sts::Engine::is_key_pressed(sts::KeyCode::E)) {
        delta.y = -5;
    }
    if(sts::Engine::is_key_pressed(sts::KeyCode::D)) {
        delta.y = 5;
    }
}

void update() {
    player.x += delta.x;
    player.y += delta.y;
}

void draw(const std::shared_ptr<sts::Renderer>& renderer) {
    renderer->clear();
    renderer->draw_filled_rect(player, sts::Color::CYAN);
    renderer->draw_filled_circle(200, 200, 32, sts::Color::PLUM);
    renderer->present();
}

int main(int argc, char* argv[]) {
    try {
        auto const renderer = sts::Engine::create_renderer(640, 400, "Stellar Salvage");
        if(!renderer) {
            spdlog::error("could not initialize renderer");
            return -1;
        }
        auto constexpr update_rate = std::chrono::milliseconds{1000 / 60};

        auto lastUpdateTime = std::chrono::system_clock::now();
        auto lastRenderTime = std::chrono::system_clock::now();

        auto framecount = 0;

        while(sts::Engine::is_window_open()) {
            auto constexpr max_updates = 5;
            auto updates = 0;
            auto now = std::chrono::system_clock::now();

            while (std::chrono::duration_cast<std::chrono::milliseconds>(
                       now - lastUpdateTime) > update_rate &&
                   updates < max_updates)
            {
                handle_events();
                update();
                lastUpdateTime += update_rate;
                updates++;
                framecount++;
            }

            // if maybe an update tooks forever we dont want to catch up
            if (std::chrono::duration_cast<std::chrono::milliseconds>(
                    now - lastUpdateTime) > update_rate)
            {
                lastUpdateTime = now - update_rate;
            }

            draw(renderer);

            lastRenderTime = now;

            while (std::chrono::duration_cast<std::chrono::milliseconds>(
                 now - lastRenderTime) < update_rate &&
             std::chrono::duration_cast<std::chrono::milliseconds>(
                 now - lastUpdateTime) < update_rate)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds{1});
                now = std::chrono::system_clock::now();
            }
        }
    } catch(sts::EngineError const& e) {
        spdlog::error(e.what());
    }

    return 0;
}