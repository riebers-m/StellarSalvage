//
// Created by HP on 17.08.2024.
//

#ifndef COLLISION_HPP
#define COLLISION_HPP

#include "core/Vector2D.hpp"
#include "Exception.hpp"

namespace core {
    enum class CollisionAlgorithm {
        AABB, /*  Axis-Aligned Bounding Box */
        OOB, /* Oriented Bounding Box */
        BOUNDING_SPHERE,
    };

    bool collision_check_AABB(Vector2D const &pos1, Vector2D const &size1, Vector2D const &pos2, Vector2D const &size2);

    /**
     * @brief Checks for a collision between two objects using their bounding spheres.
     *
     * This function determines whether a collision has occurred by checking if the
     * bounding spheres of two objects, defined by their positions and radii, overlap.
     * The bounding sphere for each object is represented by a center position and a radius.
     *
     * @param pos1 The center position of the first object's bounding sphere.
     * @param radius1 The radius of the first object's bounding sphere.
     * @param pos2 The center position of the second object's bounding sphere.
     * @param radius2 The radius of the second object's bounding sphere.
     *
     * @return bool
     * - `true`: A collision is detected between the two bounding spheres.
     * - `false`: No collision is detected.
     *
     * The function calculates the distance between the two center positions (`pos1` and `pos2`)
     * and compares it to the sum of their radii (`radius1 + radius2`). If the distance is less
     * than or equal to the sum of the radii, the bounding spheres overlap, indicating a collision.
     *
     * Example usage:
     * @code
     * Vector2D position1(10.0, 20.0);
     * Vector2D position2(15.0, 25.0);
     * std::size_t radius1 = 5;
     * std::size_t radius2 = 5;
     *
     * if (collision_check_bounding_sphere(position1, radius1, position2, radius2)) {
     *     // Handle collision
     * } else {
     *     // No collision, proceed with normal operations
     * }
     * @endcode
     */
    bool collision_check_bounding_sphere(Vector2D const &pos1, std::size_t radius1, Vector2D const &pos2,
                                         std::size_t radius2);

    bool collision_check_oriented_bounding_sphere(Vector2D const& tl1, Vector2D const& br1, Vector2D const& tl2, Vector2D const& br2);
} // namespace core
#endif // COLLISION_HPP
