//
// Created by max on 12.07.24.
//

#include "SDLRenderer.hpp"
#include <optional>
#include <spdlog/spdlog.h>

#include "Exception.hpp"

namespace sts {
    struct RGBA {
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t a;
    };

    std::optional<RGBA> convert_to_rgba(Color color) {
        switch (color) {
            case Color::RED:
                return RGBA{255, 0, 0, 255};
            case Color::GREEN:
                return RGBA{0, 255, 0, 255};
            case Color::BLUE:
                return RGBA{0, 0, 255, 255};
            case Color::YELLOW:
                return RGBA{255, 255, 0, 255};
            case Color::ORANGE:
                return RGBA{255, 165, 0, 255};
            case Color::PURPLE:
                return RGBA{128, 0, 128, 255};
            case Color::PINK:
                return RGBA{255, 192, 203, 255};
            case Color::CYAN:
                return RGBA{0, 255, 255, 255};
            case Color::MAGENTA:
                return RGBA{255, 0, 255, 255};
            case Color::LIME:
                return RGBA{0, 255, 0, 255};
            case Color::TEAL:
                return RGBA{0, 128, 128, 255};
            case Color::LAVENDER:
                return RGBA{230, 230, 250, 255};
            case Color::BROWN:
                return RGBA{165, 42, 42, 255};
            case Color::SILVER:
                return RGBA{192, 192, 192, 255};
            case Color::GOLD:
                return RGBA{255, 215, 0, 255};
            case Color::NAVY:
                return RGBA{0, 0, 128, 255};
            case Color::INDIGO:
                return RGBA{75, 0, 130, 255};
            case Color::MAROON:
                return RGBA{128, 0, 0, 255};
            case Color::OLIVE:
                return RGBA{128, 128, 0, 255};
            case Color::CORAL:
                return RGBA{255, 127, 80, 255};
            case Color::TURQUOISE:
                return RGBA{64, 224, 208, 255};
            case Color::PLUM:
                return RGBA{221, 160, 221, 255};
            case Color::SLATE:
                return RGBA{112, 128, 144, 255};
            case Color::CRIMSON:
                return RGBA{220, 20, 60, 255};
            case Color::STEEL:
                return RGBA{70, 130, 180, 255};
            case Color::BLACK:
                return RGBA{0, 0, 0, 255};
            case Color::WHITE:
                return RGBA{255, 255, 255, 255};
            case Color::GRAY:
                return RGBA{128, 128, 128, 255};
            case Color::AQUA:
                return RGBA{0, 255, 255, 255};
            case Color::VIOLET:
                return RGBA{238, 130, 238, 255};
        }
        return {};
    }

    void SDLRenderer::set_render_color(Color color) {
        auto const rgba = convert_to_rgba(color);
        if (!rgba.has_value()) {
            spdlog::warn("invalid color value");
            return;
        }
        auto const [r, g, b, a] = rgba.value();
        if(SDL_SetRenderDrawColor(m_renderer, r, g, b, a) != 0) {
            throw EngineError(std::format("render error {}", SDL_GetError()));
        }
    }
    SDLRenderer::SDLRenderer(SDL_Renderer *renderer) : m_renderer(renderer) {}

    void SDLRenderer::draw_filled_rect(int32_t x, int32_t y, int32_t width, int32_t height, Color color) {
        draw_filled_rect(Rect{width, height, x, y}, color);
    }
    void SDLRenderer::draw_filled_rect(Rect const &rect, Color color) {
        set_render_color(color);
        SDL_Rect const sdl_rect{rect.x, rect.y, rect.width, rect.height};
        if (SDL_RenderFillRect(m_renderer, &sdl_rect) != 0) {
            throw EngineError(std::format("render error: {}", SDL_GetError()));
        }
    }
    void SDLRenderer::draw_filled_circle(int32_t center_x, int32_t center_y, size_t radius, Color color) {
        set_render_color(color);

        int const squaredRadius = static_cast<int>(radius * radius);
        int const minX = static_cast<int>(-radius);
        int const minY = static_cast<int>(-radius);
        int const maxX = static_cast<int>(radius);
        int const maxY = static_cast<int>(radius);

        for (int y = minY; y <= maxY; ++y)
        {
            for (int x = minX; x <= maxX; ++x)
            {
                auto const distanceSquared = x * x + y * y;
                if (distanceSquared <= squaredRadius)
                {
                    if(SDL_RenderDrawPoint(m_renderer, center_x + x, center_y + y) != 0) {
                        throw EngineError(std::format("render error: {}", SDL_GetError()));
                    }
                }
            }
        }
    }
    void SDLRenderer::clear() {
        if(SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255) != 0) {
            throw EngineError(std::format("render error: {}", SDL_GetError()));
        }
        if(SDL_RenderClear(m_renderer) != 0) {
            throw EngineError(std::format("render error: {}", SDL_GetError()));
        }
    }
    void SDLRenderer::present() {
        SDL_RenderPresent(m_renderer);
    }

} // namespace sts
