//
// Created by HP on 17.08.2024.
//
#include <catch2/catch_test_macros.hpp>
#include "core/Collision.hpp"

TEST_CASE("Bounding Sphere Collision Detection", "[collision_check_bounding_sphere]") {
    SECTION("Colliding spheres") {
        core::Vector2D pos2(3.0, 4.0);  // 5 units away from pos1
        core::Vector2D pos1(0.0, 0.0);
        std::size_t radius1 = 5;
        std::size_t radius2 = 1;

        REQUIRE(collision_check_bounding_sphere(pos1, radius1, pos2, radius2) == true);
    }

    SECTION("Non-colliding spheres") {
        core::Vector2D pos1(0.0, 0.0);
        core::Vector2D pos2(10.0, 10.0);  // More than 14 units away from pos1
        std::size_t radius1 = 2;
        std::size_t radius2 = 2;

        REQUIRE(collision_check_bounding_sphere(pos1, radius1, pos2, radius2) == false);
    }

    SECTION("Touching spheres") {
        core::Vector2D pos1(0.0, 0.0);
        core::Vector2D pos2(10.0, 0.0);  // Exactly 10 units away from pos1
        std::size_t radius1 = 5;
        std::size_t radius2 = 5;

        REQUIRE(collision_check_bounding_sphere(pos1, radius1, pos2, radius2) == true);
    }

    SECTION("One sphere completely inside another") {
        core::Vector2D pos1(0.0, 0.0);
        core::Vector2D pos2(1.0, 1.0);  // 1.41 units away from pos1
        std::size_t radius1 = 5;
        std::size_t radius2 = 1;

        REQUIRE(collision_check_bounding_sphere(pos1, radius1, pos2, radius2) == true);
    }

    SECTION("Identical spheres") {
        core::Vector2D pos1(0.0, 0.0);
        core::Vector2D pos2(0.0, 0.0);  // Same position as pos1
        std::size_t radius1 = 5;
        std::size_t radius2 = 5;

        REQUIRE(collision_check_bounding_sphere(pos1, radius1, pos2, radius2) == true);
    }

    SECTION("Zero radius spheres (no collision)") {
        core::Vector2D pos1(0.0, 0.0);
        core::Vector2D pos2(5.0, 5.0);  // 7.07 units away from pos1
        std::size_t radius1 = 0;
        std::size_t radius2 = 0;

        REQUIRE_THROWS_AS(collision_check_bounding_sphere(pos1, radius1, pos2, radius2), sts::CoreError);
    }
}

TEST_CASE("AABB Collision Detection with Top-Left Origin", "[collision_check_AABB]") {
    SECTION("Colliding AABBs - Overlapping") {
        core::Vector2D tl1(0.0, 0.0);   // Top-left corner at (0, 0)
        core::Vector2D br1(10.0, 10.0); // Bottom-right corner at (10, 10)
        core::Vector2D tl2(5.0, 5.0);   // Top-left corner at (5, 5)
        core::Vector2D br2(15.0, 15.0); // Bottom-right corner at (15, 15)

        REQUIRE(collision_check_AABB(tl1, br1, tl2, br2) == true);
    }

    SECTION("Non-colliding AABBs - Separated Horizontally") {
        core::Vector2D tl1(0.0, 0.0);   // Top-left corner at (0, 0)
        core::Vector2D br1(10.0, 10.0); // Bottom-right corner at (10, 10)
        core::Vector2D tl2(15.0, 0.0);  // Top-left corner at (15, 0)
        core::Vector2D br2(25.0, 10.0); // Bottom-right corner at (25, 10)

        REQUIRE(collision_check_AABB(tl1, br1, tl2, br2) == false);
    }

    SECTION("Non-colliding AABBs - Separated Vertically") {
        core::Vector2D tl1(0.0, 0.0);   // Top-left corner at (0, 0)
        core::Vector2D br1(10.0, 10.0); // Bottom-right corner at (10, 10)
        core::Vector2D tl2(0.0, 15.0);  // Top-left corner at (0, 15)
        core::Vector2D br2(10.0, 25.0); // Bottom-right corner at (10, 25)

        REQUIRE(collision_check_AABB(tl1, br1, tl2, br2) == false);
    }

    SECTION("Touching AABBs - Sharing Edge") {
        core::Vector2D tl1(0.0, 0.0);   // Top-left corner at (0, 0)
        core::Vector2D br1(10.0, 10.0); // Bottom-right corner at (10, 10)
        core::Vector2D tl2(10.0, 0.0);  // Top-left corner at (10, 0)
        core::Vector2D br2(20.0, 10.0); // Bottom-right corner at (20, 10)

        REQUIRE(collision_check_AABB(tl1, br1, tl2, br2) == true);
    }

    SECTION("Touching AABBs - Sharing Corner") {
        core::Vector2D tl1(0.0, 0.0);    // Top-left corner at (0, 0)
        core::Vector2D br1(10.0, 10.0);  // Bottom-right corner at (10, 10)
        core::Vector2D tl2(10.0, 10.0);  // Top-left corner at (10, 10)
        core::Vector2D br2(20.0, 20.0);  // Bottom-right corner at (20, 20)

        REQUIRE(collision_check_AABB(tl1, br1, tl2, br2) == true);
    }

    SECTION("Identical AABBs") {
        core::Vector2D tl1(0.0, 0.0);   // Top-left corner at (0, 0)
        core::Vector2D br1(10.0, 10.0); // Bottom-right corner at (10, 10)
        core::Vector2D tl2(0.0, 0.0);   // Top-left corner at (0, 0)
        core::Vector2D br2(10.0, 10.0); // Bottom-right corner at (10, 10)

        REQUIRE(collision_check_AABB(tl1, br1, tl2, br2) == true);
    }

    SECTION("One AABB Completely Inside Another") {
        core::Vector2D tl1(0.0, 0.0);   // Top-left corner at (0, 0)
        core::Vector2D br1(20.0, 20.0); // Bottom-right corner at (20, 20)
        core::Vector2D tl2(5.0, 5.0);   // Top-left corner at (5, 5)
        core::Vector2D br2(15.0, 15.0); // Bottom-right corner at (15, 15)

        REQUIRE(collision_check_AABB(tl1, br1, tl2, br2) == true);
    }

    SECTION("Non-colliding AABBs - Outside of each other") {
        core::Vector2D tl1(0.0, 0.0);   // Top-left corner at (0, 0)
        core::Vector2D br1(10.0, 10.0); // Bottom-right corner at (10, 10)
        core::Vector2D tl2(11.0, 11.0); // Top-left corner at (11, 11)
        core::Vector2D br2(20.0, 20.0); // Bottom-right corner at (20, 20)

        REQUIRE(collision_check_AABB(tl1, br1, tl2, br2) == false);
    }
}