//
// Created by max on 13.07.24.
//

#ifndef STELLAR_SALVAGE_DETAILS_HPP
#define STELLAR_SALVAGE_DETAILS_HPP

#include <SDL.h>
#include <string>
#include <memory>

namespace sts {

class Details {
public:
  Details();
  ~Details();

  Details(Details const &) = delete;
  Details &operator=(Details const &) noexcept = delete;
  Details(Details &&) = delete;
  Details &&operator=(Details &&) noexcept = delete;

  void init_window_and_renderer(size_t width, size_t height,
                                std::string const &title);

  SDL_Window *get_window() const;
  SDL_Renderer *get_renderer() const;

private:
  struct SDL_Deleter {
    void operator()(SDL_Renderer *ptr) const {
      if (ptr) {
        SDL_DestroyRenderer(ptr);
      }
    }
    void operator()(SDL_Window *ptr) const {
      if (ptr) {
        SDL_DestroyWindow(ptr);
      }
    }
  };

  std::unique_ptr<SDL_Window, SDL_Deleter> m_window;
  std::unique_ptr<SDL_Renderer, SDL_Deleter> m_renderer;
};

} // namespace sts

#endif // STELLAR_SALVAGE_DETAILS_HPP
