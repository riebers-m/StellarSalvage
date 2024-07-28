//
// Created by max on 13.07.24.
//

#ifndef STELLAR_SALVAGE_ENGINE_HPP
#define STELLAR_SALVAGE_ENGINE_HPP

#include <memory>
#include <string>
#include "Renderer.hpp"

namespace sts {
    class Details;

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

    private:
        Engine();

        static Engine const &instance();
    };
} // namespace sts
#endif // STELLAR_SALVAGE_ENGINE_HPP
