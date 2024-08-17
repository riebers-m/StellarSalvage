//
// Created by HP on 17.08.2024.
//

#include "core/Collision.hpp"
#include "Exception.hpp"

namespace core {
    bool collision_check_AABB(Vector2D const& pos1, Vector2D const& size1, Vector2D const& pos2, Vector2D const& size2) {
        throw sts::CoreError("Not implemented yet");
    }

    bool collision_check_bounding_sphere(Vector2D const& pos1, std::size_t radius1, Vector2D const& pos2, std::size_t radius2) {
        if(radius1 == 0 || radius2 == 0) {
            throw sts::CoreError(std::format("invalid radius: {}, {}", radius1, radius2));
        }
        auto const distance = magnitude(subtract(pos1, pos2));
        return (static_cast<float>(radius1+radius2)-distance) > 0.001;
    }
}