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

    ShipState create_ship(Vector2D const& pos, float veclocity_limit, float acceleration_limit, float friction);

    ShipState update_ship_position(ShipState const& ship);

} // namespace core
#endif //SPACESHIP_HPP
