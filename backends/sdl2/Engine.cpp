//
// Created by max on 13.07.24.
//

#include "Engine.hpp"
#include "Details.hpp"
#include "Exception.hpp"
#include "SDLRenderer.hpp"

namespace sts {
    static std::unique_ptr<Details> m_details{nullptr};

    Engine const &Engine::instance() {
        static auto engine = Engine{};
        return engine;
    }
    std::shared_ptr<Renderer> Engine::create_renderer(size_t window_width, size_t window_height,
                                                      std::string const &window_title, Engine const &engine) {
        if (m_details == nullptr) {
            m_details = std::make_unique<Details>();
        }

        if (m_details->get_renderer() == nullptr && m_details->get_window() == nullptr) {
            m_details->init_window_and_renderer(window_width, window_height, window_title);
        }
        if (SDL_Renderer *renderer = m_details->get_renderer(); renderer != nullptr) {
            return std::make_shared<SDLRenderer>(renderer);
        }
        throw EngineError(std::format("renderer not properly initialized"));
    }
    Engine::Engine() {
        // Setup code here
    }
    Engine::~Engine() {
        SDL_Quit();
    }
} // namespace sts
