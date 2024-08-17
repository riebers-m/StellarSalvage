//
// Created by HP on 17.08.2024.
//

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "core/Vector2D.hpp"

namespace core {
    enum class CollisionAlgorithm {
        AABB,   /*  Axis-Aligned Bounding Box */
        OOB,    /* Oriented Bounding Box */
        BOUNDING_SPHERE,
    };

    bool collision_check_AABB(Vector2D const& pos1, Vector2D const& size1, Vector2D const& pos2, Vector2D const& size2);
    bool collision_check_bounding_sphere(Vector2D const& pos1, std::size_t radius1, Vector2D const& pos2, std::size_t radius2);
}
#endif //COLLISION_HPP
