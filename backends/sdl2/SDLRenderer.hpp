//
// Created by max on 12.07.24.
//

#ifndef STELLAR_SALVAGE_SDLRENDERER_HPP
#define STELLAR_SALVAGE_SDLRENDERER_HPP
#include <SDL2/SDL.h>
#include "Renderer.hpp"

namespace sts {

    class SDLRenderer : public Renderer {
    public:
        explicit SDLRenderer(SDL_Renderer *);

        void draw_filled_rect(int32_t x, int32_t y, int32_t width, int32_t height, Color) override;
        void draw_filled_rect(Rect const &, Color) override;
        void draw_filled_circle(int32_t center_x, int32_t center_y, size_t radius, Color) override;
        void clear() override;

        void present() override;

    private:
        void set_render_color(Color);

        SDL_Renderer *m_renderer;
    };

} // namespace sts

#endif // STELLAR_SALVAGE_SDLRENDERER_HPP
