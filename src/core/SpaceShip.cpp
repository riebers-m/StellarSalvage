//
// Created by HP on 11.08.2024.
//
#include "core/SpaceShip.hpp"

namespace core {

    ShipState new_ship_position(Vector2D const &current_pos, Vector2D const &mouse_pos, Vector2D const &velocity,
                                Vector2D const &acceleration, float acceleration_limit, float velocity_limit) {
        auto const new_acceleration = set_limit(subtract(mouse_pos, current_pos), acceleration_limit);
        auto const new_velocity = set_limit(add(velocity, new_acceleration), velocity_limit);
        auto const new_pos = add(current_pos, new_velocity);
        return {new_pos, new_velocity, new_acceleration};
    }

    ShipState update_ship_position(ShipState const& ship) {
        auto const acceleration = set_limit(ship.acc, 2);
        auto const new_velocity = set_limit(add(ship.vel, acceleration), 4);
        auto const new_position = add(ship.pos, new_velocity);

        return {new_position, new_velocity, Vector2D{0,0}};
    }
} // namespace core
