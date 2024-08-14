//
// Created by HP on 11.08.2024.
//

#ifndef SPACESHIP_HPP
#define SPACESHIP_HPP

#include "core/Vector2D.hpp"

namespace core {
    struct ShipState {
        Vector2D pos;
        Vector2D vel;
        Vector2D acc;
    };

    /**
    * @brief Calculate the new position and velocity of the spaceship.
    *
    * This function computes the spaceship's movement towards the target (mouse position)
    * while considering acceleration and velocity limits for realistic and smooth movement.
    *
    * @param current_pos The current position of the spaceship in 2D space.
    * @param mouse_pos The target position (mouse pointer) in 2D space.
    * @param velocity The current velocity of the spaceship.
    * @param acceleration_limit The maximum allowable acceleration for the spaceship.
    * @param velocity_limit The maximum allowable velocity for the spaceship.
    *
    * @return std::pair<Vector2D, Vector2D>
    *         - First: The new position of the spaceship after applying the updated velocity.
    *         - Second: The updated velocity of the spaceship after applying acceleration and limiting the speed.
    */
    ShipState new_ship_position(Vector2D const &current_pos, Vector2D const &mouse_pos, Vector2D const &velocity,
                                Vector2D const &acceleration, float acceleration_limit = 5,
                               float velocity_limit = 10);
    ShipState update_ship_position(ShipState const& ship);
} // namespace core
#endif //SPACESHIP_HPP
