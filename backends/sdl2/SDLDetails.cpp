//
// Created by max on 13.07.24.
//

#include "Details.hpp"
#include "Exception.hpp"
#include <spdlog/spdlog.h>

namespace sts {
Details::Details() : m_window(nullptr), m_renderer(nullptr) {
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
                 "SDL could not initialize SDL! SDL_Error: %s", SDL_GetError());
    throw EngineError("SDL could not initialize");
  }
  // if (TTF_Init() < 0) {
  //   SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
  //                "SDL could not initialize TTF! SDL_Error: %s", TTF_GetError());
  //   throw EngineError("SDL could not initialize ttf");
  // }
}
void Details::init_window_and_renderer(size_t width, size_t height,
                                       std::string const &title) {
  if (SDL_Window *window = SDL_CreateWindow(
          title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
          static_cast<int>(width), static_cast<int>(height), SDL_WINDOW_SHOWN);
      window != nullptr) {
    m_window.reset(window);
    if (SDL_Renderer *renderer =
            SDL_CreateRenderer(m_window.get(), -1, SDL_RENDERER_ACCELERATED);
        renderer != nullptr) {
      m_renderer.reset(renderer);
      SDL_SetRenderDrawBlendMode(m_renderer.get(), SDL_BLENDMODE_BLEND);
      return;
    }
    spdlog::error(std::format(
        "SDL could not initialize renderer! SDL_Error: {}", SDL_GetError()));
    throw EngineError("SDL initialize renderer failed");
  }
  spdlog::error(std::format("SDL could not initialize window! SDL_Error: {}",
                            SDL_GetError()));
  throw EngineError("SDL initialize window failed");
}
} // namespace sts