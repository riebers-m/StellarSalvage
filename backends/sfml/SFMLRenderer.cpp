//
// Created by HP on 28.07.2024.
//

#include "SFMLRenderer.hpp"
sts::SFMLRenderer::SFMLRenderer(sf::RenderWindow *) {}
void sts::SFMLRenderer::draw_filled_rect(int32_t x, int32_t y, int32_t width, int32_t height, Color) {}
void sts::SFMLRenderer::draw_filled_rect(Rect const &, Color) {}
void sts::SFMLRenderer::draw_filled_circle(int32_t center_x, int32_t center_y, size_t radius, Color) {}
void sts::SFMLRenderer::clear() {}
void sts::SFMLRenderer::present() {}
void sts::SFMLRenderer::set_render_color(Color) {}
