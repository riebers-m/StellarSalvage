//
// Created by HP on 23.08.2024.
//

#ifndef ENTITYCOMPONENTSYSTEM_HPP
#define ENTITYCOMPONENTSYSTEM_HPP
#include <array>
#include <queue>
#include <unordered_map>
#include <unordered_set>

#include "Exception.hpp"


namespace core {
    using Entity = std::size_t;

    struct Entities {
        std::queue<Entity> available_entities{};
        std::unordered_set<Entity> living_entities{};
        std::size_t totoal_entity_count{};
    };

    /**
     * @brief Creates a new entity within the provided Entities struct.
     *
     * This function generates a new entity ID, adds it to the set of living entities,
     * and returns the updated Entities struct along with the newly created entity.
     *
     * If there are available entities in the `available_entities` queue (previously destroyed),
     * the function will reuse one of these IDs. Otherwise, it will create a new entity using
     * the `entity_count` counter.
     *
     * @param entities The current state of the Entities struct.
     * @return std::pair<Entity, Entities> A pair containing the newly created entity and
     * the updated Entities struct.
     *
     * @note The entity ID is guaranteed to be unique within the Entities struct.
     */
    std::pair<Entity, Entities> create_entity(Entities && entities) noexcept;

    /**
     * @brief Destroys an existing entity within the provided Entities struct.
     *
     * This function removes the specified entity from the set of living entities
     * and adds it to the queue of available entities for reuse.
     *
     * @param entity The entity ID to be destroyed.
     * @param entities The current state of the Entities struct.
     * @return std::pair<sts::error, Entities> A pair containing a enum indicating
     * success and the updated Entities struct. If the entity exists
     * and is successfully destroyed, the function returns `sts::error::ok` along with the updated
     * Entities struct. If the entity does not exist, the function returns `sts::error::invalid_entity`.
     *
     * @note The function does not throw errors but will return `false` if the
     * entity is not found in the set of living entities.
     */
    std::pair<sts::error, Entities> destroy_entity(Entity entity, Entities && entities) noexcept;

    template<typename T, std::size_t N>
    struct ComponentBase {
        std::unordered_map<Entity, std::size_t> entity_to_index{};
        std::unordered_map<std::size_t, Entity> index_to_entity{};
        std::size_t entity_count{};
        using ComponentArray = std::array<T, N>;
        ComponentArray components;
    };

    template<typename Component, typename T, std::size_t N>
    std::pair<sts::error, ComponentBase<T, N>> add_component(Entity entity, Component const &component,
                                                          ComponentBase<T, N> && component_array) {
        static_assert(std::is_same_v<T, Component>, "Component <-> ComponentBase type miss match.");
        if (component_array.entity_to_index.contains(entity)) {
            return std::make_pair(sts::error::entity_exists, component_array);
        }
        if (auto const new_index = component_array.entity_count; new_index < N) {
            component_array.entity_to_index[entity] = new_index;
            component_array.index_to_entity[new_index] = entity;
            ++component_array.entity_count;
            component_array.components[new_index] = component;
            return std::make_pair(sts::error::ok, component_array);
        }

        return std::make_pair(sts::error::entity_limit, component_array);
    }

    template<typename T, std::size_t N>
    std::pair<sts::error, ComponentBase<T,N>> delete_component(Entity entity, ComponentBase<T, N> &&component_array) {
        if(auto const removed_entity=component_array.entity_to_index.find(entity);removed_entity!=component_array.entity_to_index.end()) {
            auto const index_removed_entity = removed_entity->second;
            auto const index_last_entity = component_array.entity_count-1;
            component_array.components[index_removed_entity] = component_array.components[index_last_entity];

            auto const last_entity = component_array.index_to_entity[index_last_entity];
            component_array.entity_to_index[last_entity] = index_removed_entity;
            component_array.index_to_entity[index_removed_entity] = last_entity;

            component_array.entity_to_index.erase(entity);
            component_array.index_to_entity.erase(index_last_entity);
            --component_array.entity_count;
            return std::make_pair(sts::error::ok, std::move(component_array));
        }
        return std::make_pair(sts::error::invalid_entity, std::move(component_array));
    }

    template<typename T, std::size_t N>
    std::optional<T> get_component(Entity entity, ComponentBase<T,N> const& component_array) {
        if(auto const searched_entity=component_array.entity_to_index.find(entity);searched_entity!=component_array.entity_to_index.end()) {
            return component_array.components.at(searched_entity->second);
        }
        return {};
    }

} // namespace core
#endif // ENTITYCOMPONENTSYSTEM_HPP
