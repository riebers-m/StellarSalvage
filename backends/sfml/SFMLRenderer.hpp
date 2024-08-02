//
// Created by HP on 28.07.2024.
//

#ifndef SFMLRENDERER_H
#define SFMLRENDERER_H

#include "Renderer.hpp"
#include <SFML/Graphics.hpp>

namespace sts{

class SFMLRenderer : public Renderer {
public:
    explicit SFMLRenderer(sf::RenderWindow *);

    void draw_filled_rect(int32_t x, int32_t y, int32_t width, int32_t height, Color) override;
    void draw_filled_rect(Rect const &, Color) override;
    void draw_filled_circle(int32_t center_x, int32_t center_y, size_t radius, Color) override;
    void clear() override;

    void present() override;

private:
    void set_render_color(Color);

    sf::RenderWindow *m_window;
};

}

#endif //SFMLRENDERER_H
