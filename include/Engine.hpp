//
// Created by max on 13.07.24.
//

#ifndef STELLAR_SALVAGE_ENGINE_HPP
#define STELLAR_SALVAGE_ENGINE_HPP

#include <memory>
#include <string>
#include "Renderer.hpp"
#include "KeyCode.hpp"
#include "core/Vector2D.hpp"

namespace sts {
    class Engine {
    public:
        Engine(Engine const &) = delete;
        Engine(Engine &&) = delete;
        Engine &operator=(Engine const &) = delete;
        Engine &operator=(Engine &&) = delete;
        ~Engine();


        [[nodiscard]] static std::shared_ptr<Renderer> create_renderer(size_t window_width, size_t window_height,
                                                                std::string const &window_title,
                                                                Engine const &engine = instance());
        static bool is_window_open();
        static bool window_focused();
        static bool is_key_pressed(KeyCode);
        static bool is_mouse_pressed(MouseButton);
        static std::optional<core::Vector2D> get_mouse_position();
    private:
        Engine();

        static Engine const &instance();
    };
} // namespace sts
#endif // STELLAR_SALVAGE_ENGINE_HPP
