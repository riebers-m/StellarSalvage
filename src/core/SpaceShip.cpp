//
// Created by HP on 11.08.2024.
//
#include "core/SpaceShip.hpp"
#include "spdlog/spdlog.h"

namespace core {
    static Vector2D apply_friction(Vector2D const &vel, Vector2D const &acc, float friction) {
        auto const normal_vec = core::multiply(vel, -1);
        if (auto const norm_friction = normalize(normal_vec); norm_friction.has_value()) {
            auto const applied_friction = multiply(norm_friction.value(), friction);
            return core::add(acc, set_limit(applied_friction, 0.1));
        }
        return acc;
    }

    ShipState create_ship(Vector2D const& pos, float veclocity_limit, float acceleration_limit, float friction) {
        return ShipState{pos, Vector2D{0,0}, Vector2D{0,0}, veclocity_limit, acceleration_limit, friction};
    }

    ShipState update_ship_position(ShipState const &ship) {
        auto const acceleration = apply_friction(ship.vel, ship.acc, ship.friction);
        auto const new_velocity = set_limit(add(ship.vel, acceleration), ship.velocity_limit);
        auto const new_position = add(ship.pos, new_velocity);
        return {new_position, new_velocity, Vector2D{0, 0}, ship.velocity_limit, ship.acceleration_limit, ship.friction};
    }
} // namespace core
