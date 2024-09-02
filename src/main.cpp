//
// Created by max on 12.07.24.
//

#include <format>
#include <spdlog/spdlog.h>
#include "Engine.hpp"
#include "Exception.hpp"
#include "core/SpaceShip.hpp"
#include "core/Vector2D.hpp"

using namespace std::chrono_literals;

core::ShipState space_ship = core::create_ship(core::Vector2D{200,200}, 4, 1.5, .15);

sts::Rect player{32, 32, 200, 200};
core::Vector2D delta{0, 0};

core::Vector2D rocket{100, 100};
core::Vector2D rocket_delta{0, 0};

bool update_space_pos = false;

void handle_ship() {
    update_space_pos = false;
    if (sts::Engine::is_key_pressed(sts::KeyCode::A)) {
        update_space_pos = true;
    }
}

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

void handle_events() { handle_ship(); }

void update_ship() {
    if (update_space_pos) {
        if (auto const mouse_pos = sts::Engine::get_mouse_position(); mouse_pos.has_value()) {
            auto const direction = core::subtract(mouse_pos.value(), space_ship.pos);
            if(auto const direction_length = core::magnitude(direction);direction_length > 40) {
                space_ship.acc = set_limit(direction, space_ship.acceleration_limit);
            }
        }
    }
    space_ship = core::update_ship_position(space_ship);
}

void update() {
    update_ship();
}

void draw(const std::shared_ptr<sts::Renderer> &renderer) {
    renderer->clear();
    renderer->draw_filled_rect(player, sts::Color::CYAN);
    spdlog::info(std::format("pos: {},{}", space_ship.pos.x, space_ship.pos.y));
    renderer->draw_filled_circle(static_cast<int32_t>(space_ship.pos.x), static_cast<int32_t>(space_ship.pos.y), 32,
                                 sts::Color::VIOLET);
    renderer->present();
}

int main(int argc, char *argv[]) {
    try {
        auto const renderer = sts::Engine::create_renderer(1080, 720, "Stellar Salvage");
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
