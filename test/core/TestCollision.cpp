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