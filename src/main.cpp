//
// Created by max on 12.07.24.
//

#include <format>
#include <iostream>
#include <spdlog/spdlog.h>
#include "Engine.hpp"
#include "Exception.hpp"
#include "core/Vector2D.hpp"

using namespace std::chrono_literals;

sts::Rect player{32, 32, 200, 200};
core::Vector2D delta{0, 0};

core::Vector2D rocket{100, 100};
core::Vector2D rocket_delta{0, 0};

void handle_keyboard() {
    delta.x = 0;
    delta.y = 0;
    if (sts::Engine::is_key_pressed(sts::KeyCode::S)) {
        delta.x = -5;
    }
    if (sts::Engine::is_key_pressed(sts::KeyCode::F)) {
        delta.x = 5;
    }
    if (sts::Engine::is_key_pressed(sts::KeyCode::E)) {
        delta.y = -5;
    }
    if (sts::Engine::is_key_pressed(sts::KeyCode::D)) {
        delta.y = 5;
    }
}

void handle_mouse() {
    rocket_delta = core::Vector2D{0, 0};

    if (sts::Engine::is_mouse_pressed(sts::MouseButton::Right)) {
        if (auto const mouse_pos = sts::Engine::get_mouse_position(); mouse_pos.has_value()) {
            rocket_delta = core::subtract(mouse_pos.value(), rocket);
            rocket_delta = core::set_limit(rocket_delta, 4);
        }
    }
}

void handle_events() {
    handle_keyboard();
    handle_mouse();
}

void update() {
    player.x += static_cast<int32_t>(delta.x);
    player.y += static_cast<int32_t>(delta.y);

    rocket = core::add(rocket, rocket_delta);
}

void draw(const std::shared_ptr<sts::Renderer> &renderer) {
    renderer->clear();
    renderer->draw_filled_rect(player, sts::Color::CYAN);
    renderer->draw_filled_circle(static_cast<int32_t>(rocket.x), static_cast<int32_t>(rocket.y), 32, sts::Color::PLUM);
    renderer->present();
}

int main(int argc, char *argv[]) {
    try {
        auto const renderer = sts::Engine::create_renderer(640, 400, "Stellar Salvage");
        if (!renderer) {
            spdlog::error("could not initialize renderer");
            return -1;
        }
        auto constexpr update_rate = std::chrono::milliseconds{1000 / 60};

        auto lastUpdateTime = std::chrono::system_clock::now();
        auto lastRenderTime = std::chrono::system_clock::now();

        auto framecount = 0;

        while (sts::Engine::is_window_open()) {
            auto constexpr max_updates = 5;
            auto updates = 0;
            auto now = std::chrono::system_clock::now();

            while (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTime) > update_rate &&
                   updates < max_updates) {
                handle_events();
                update();
                lastUpdateTime += update_rate;
                updates++;
                framecount++;
            }

            // if maybe an update tooks forever we dont want to catch up
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTime) > update_rate) {
                lastUpdateTime = now - update_rate;
            }

            draw(renderer);

            lastRenderTime = now;

            while (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRenderTime) < update_rate &&
                   std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTime) < update_rate) {
                std::this_thread::sleep_for(std::chrono::milliseconds{1});
                now = std::chrono::system_clock::now();
            }
        }
    } catch (sts::EngineError const &e) {
        spdlog::error(e.what());
    }

    return 0;
}
