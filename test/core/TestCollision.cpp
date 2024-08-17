//
// Created by HP on 17.08.2024.
//
#include <catch2/catch_test_macros.hpp>
#include "core/Collision.hpp"

TEST_CASE("SimpleCollision1", "[bounding_sphere]") {
    core::Vector2D const pos1{200,200};
    auto constexpr radius1 = 32;

    core::Vector2D const pos2{263,200};
    auto constexpr radius2 = 32;

    REQUIRE(core::collision_check_bounding_sphere(pos1, radius1, pos2, radius2));
}

TEST_CASE("SimpleCollision2", "[bounding_sphere]") {
    core::Vector2D const pos1{263,200};
    auto constexpr radius1 = 32;

    core::Vector2D const pos2{200,200};
    auto constexpr radius2 = 32;

    REQUIRE(core::collision_check_bounding_sphere(pos1, radius1, pos2, radius2));
}