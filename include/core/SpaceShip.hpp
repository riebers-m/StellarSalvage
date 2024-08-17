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
        float velocity_limit{};
        float acceleration_limit{};
        float friction{};
    };

    /**
     * @brief Creates and initializes a new ship with the given parameters.
     *
     * This function constructs a ShipState object that represents the state of a spaceship in the game.
     * The ship is initialized with a specific position, velocity limit, acceleration limit, and friction coefficient.
     *
     * @param pos A constant reference to a Vector2D object that specifies the initial position of the ship in 2D space.
     * @param velocity_limit A float value representing the maximum speed (velocity) the ship can achieve.
     * @param acceleration_limit A float value representing the maximum acceleration the ship can have.
     * @param friction A float value representing the friction applied to the ship, affecting how quickly it slows down
     * when no force is applied.
     *
     * @return ShipState A ShipState object containing the initialized state of the ship.
     */

    ShipState create_ship(Vector2D const &pos, float veclocity_limit, float acceleration_limit, float friction);

    /**
     * @brief Updates the position and velocity of the ship based on its current state.
     *
     * This function calculates the new position and velocity of the ship by applying its current acceleration,
     * velocity limit, acceleration limit, and friction. The updated position and velocity are returned in a new
     * ShipState object.
     *
     * The update process includes:
     * - Applying the acceleration to the current velocity, considering the acceleration limit.
     * - Applying friction to reduce the velocity proportionally.
     * - Clamping the velocity to the specified velocity limit.
     * - Updating the position based on the new velocity.
     *
     * @param ship A constant reference to a ShipState object representing the current state of the ship,
     * including its position, velocity, acceleration, and limits.
     *
     * @return ShipState A new ShipState object with the updated position, velocity, and other properties.
     */

    ShipState update_ship_position(ShipState const &ship);

} // namespace core
#endif // SPACESHIP_HPP
