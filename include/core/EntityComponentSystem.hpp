//
// Created by HP on 23.08.2024.
//

#ifndef ENTITYCOMPONENTSYSTEM_HPP
#define ENTITYCOMPONENTSYSTEM_HPP
#include <set>
namespace core {
    using Entity = std::size_t;
    using Entities = std::set<Entity>;

    std::pair<Entity, Entities> create_entity(Entities, std::size_t max_entity_count = 1000);
} // namespace core
#endif //ENTITYCOMPONENTSYSTEM_HPP
