//
// Created by max on 12.07.24.
//

#ifndef STELLAR_SALVAGE_RENDERER_HPP
#define STELLAR_SALVAGE_RENDERER_HPP
#include <cstdint>
#include <cstddef>
namespace sts {
    enum class Color
    {
        RED,
        GREEN,
        BLUE,
        YELLOW,
        ORANGE,
        PURPLE,
        PINK,
        CYAN,
        MAGENTA,
        LIME,
        TEAL,
        LAVENDER,
        BROWN,
        SILVER,
        GOLD,
        NAVY,
        INDIGO,
        MAROON,
        OLIVE,
        CORAL,
        TURQUOISE,
        PLUM,
        SLATE,
        CRIMSON,
        STEEL,
        BLACK,
        WHITE,
        GRAY,
        AQUA,
        VIOLET
    };

    struct Rect {
        int32_t width{0};
        int32_t height{0};
        int32_t x{0};
        int32_t y{0};
    };
    class Renderer {
    public:
        virtual ~Renderer()= default;

        virtual void draw_filled_rect(int32_t x, int32_t y, int32_t width, int32_t height, Color) = 0;
        virtual void draw_filled_rect(Rect const&, Color) = 0;
        virtual void draw_filled_circle(int32_t center_x, int32_t center_y, size_t radius, Color) = 0;
        virtual void clear() = 0;
        virtual void present() = 0;
    };
}


#endif //STELLAR_SALVAGE_RENDERER_HPP
