//
// Created by HP on 17.08.2024.
//

#include "core/Collision.hpp"

namespace core {
    /**
     * @brief Checks for a collision between two axis-aligned bounding boxes (AABB).
     *
     * This function determines whether two axis-aligned bounding boxes (AABB) collide.
     * Each bounding box is defined by its top-left (tl) and bottom-right (br) corners.
     * The function checks if the two bounding boxes overlap on both the x and y axes.
     *
     * @param tl1 The top-left corner of the first bounding box.
     * @param br1 The bottom-right corner of the first bounding box.
     * @param tl2 The top-left corner of the second bounding box.
     * @param br2 The bottom-right corner of the second bounding box.
     *
     * @return bool
     * - `true`: A collision is detected between the two AABBs.
     * - `false`: No collision is detected.
     *
     * The function determines whether the bounding boxes are intersecting by comparing
     * the positions of their edges. Specifically, it checks whether one box is completely
     * to the left, right, above, or below the other. If none of these conditions are met,
     * the boxes overlap, indicating a collision.
     *
     * Example usage:
     * @code
     * Vector2D tl1(0.0, 10.0);
     * Vector2D br1(10.0, 0.0);
     * Vector2D tl2(5.0, 15.0);
     * Vector2D br2(15.0, 5.0);
     *
     * if (collision_check_AABB(tl1, br1, tl2, br2)) {
     *     // Handle collision
     * } else {
     *     // No collision, proceed with normal operations
     * }
     * @endcode
     */
    bool collision_check_AABB(Vector2D const &tl1, Vector2D const &br1, Vector2D const &tl2, Vector2D const &br2) {
        // rectangles are next to each other
        if (tl1.x > br2.x || br1.x < tl2.x) {
            return false;
        }

        // rects are above each other
        if (tl1.y > br2.y || br1.y < tl2.y) {
            return false;
        }
        return true;
    }

    bool collision_check_bounding_sphere(Vector2D const &pos1, std::size_t radius1, Vector2D const &pos2,
                                         std::size_t radius2) {
        if (radius1 == 0 || radius2 == 0) {
            throw sts::CoreError(std::format("invalid radius: {}, {}", radius1, radius2));
        }
        auto const distance = magnitude(subtract(pos1, pos2));
        return (static_cast<float>(radius1 + radius2) - distance) >= 0;
    }

    bool collision_check_oriented_bounding_sphere(Vector2D const &tl1, Vector2D const &br1, Vector2D const &tl2,
                                                  Vector2D const &br2) {
        throw sts::CoreError("Not implemented yet.");
    }
} // namespace core
