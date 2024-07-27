//
// Created by max on 12.07.24.
//

#ifndef STELLAR_SALVAGE_SDLRENDERER_HPP
#define STELLAR_SALVAGE_SDLRENDERER_HPP
#include "Renderer.hpp"
#include "SDL.h"
#include <memory>

namespace sts {

class SDLRenderer : public Renderer {
public:
  explicit SDLRenderer(SDL_Renderer *);

  void draw_rect(int32_t x, int32_t y, int32_t width, int32_t height,
                 Color) override;
  void draw_rect(Rect const &, Color) override;
  void draw_circle(int32_t x, int32_t y, size_t radius, Color) override;
  void clear() override;

private:
  void set_render_color(Color);

  SDL_Renderer *m_renderer;
};

} // namespace sts

#endif // STELLAR_SALVAGE_SDLRENDERER_HPP
