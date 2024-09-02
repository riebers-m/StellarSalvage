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
        std::size_t total_entity_count{};
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
    std::pair<Entity, Entities> create_entity(Entities &&entities) noexcept;

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
    std::pair<sts::error, Entities> destroy_entity(Entity entity, Entities &&entities) noexcept;

    template<typename T, std::size_t N>
    struct ComponentBase {
        std::unordered_map<Entity, std::size_t> entity_to_index{};
        std::unordered_map<std::size_t, Entity> index_to_entity{};
        std::size_t entity_count{};
        using ComponentArray = std::array<T, N>;
        ComponentArray components;
    };

    /**
     * @brief Adds a component to the specified entity within the component array.
     *
     * This function attempts to add a given component to the entity in the provided component array.
     * If the entity already has a component in the array, the function returns an error and the
     * original component array. Otherwise, the component is added, the entity and component mappings
     * are updated, and the modified component array is returned.
     *
     * @tparam Component The type of the component being added.
     * @tparam T The type of the elements stored within the ComponentBase's component array.
     * @tparam N The maximum number of components that the ComponentBase can hold.
     *
     * @param entity The entity to which the component is being added.
     * @param component The component to add to the entity.
     * @param component_array The component array to which the component will be added. This parameter
     *                        is passed as an rvalue reference, allowing the function to take ownership
     *                        of it and modify it directly without unnecessary copies.
     *
     * @return A pair consisting of:
     *         - `sts::error`: A status indicating whether the operation was successful or if the entity
     *           already had a component (resulting in an error).
     *         - `ComponentBase<T, N>`: The updated component array after the operation.
     */
    template<typename Component, typename T, std::size_t N>
    std::pair<sts::error, ComponentBase<T, N>> add_component(Entity entity, Component const &component,
                                                             ComponentBase<T, N> &&component_array) {
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

    /**
     * @brief Removes a component associated with a specific entity from the component array.
     *
     * This function attempts to delete a component that is associated with a given entity in the
     * provided component array. If the entity is found, the component is removed, and the array is
     * reorganized to maintain a contiguous block of active components. The last component in the array
     * is moved to the location of the removed component to fill the gap, and the mappings between
     * entities and components are updated accordingly.
     *
     * @tparam T The type of the components stored within the ComponentBase's component array.
     * @tparam N The maximum number of components that the ComponentBase can hold.
     *
     * @param entity The entity whose component is to be deleted.
     * @param component_array The component array from which the component will be deleted. This
     *                        parameter is passed as an rvalue reference, allowing the function to take
     *                        ownership of it and modify it directly without unnecessary copies.
     *
     * @return A pair consisting of:
     *         - `sts::error`: A status indicating whether the deletion was successful (`sts::error::ok`)
     *           or if the entity was not found in the component array (`sts::error::invalid_entity`).
     *         - `ComponentBase<T, N>`: The updated component array after the operation.
     */
    template<typename T, std::size_t N>
    std::pair<sts::error, ComponentBase<T, N>> delete_component(Entity entity, ComponentBase<T, N> &&component_array) {
        if (auto const removed_entity = component_array.entity_to_index.find(entity);
            removed_entity != component_array.entity_to_index.end()) {
            auto const index_removed_entity = removed_entity->second;
            auto const index_last_entity = component_array.entity_count - 1;
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
    std::pair<sts::error, ComponentBase<T, N>> update_component(Entity entity, T const &new_value,
                                                                ComponentBase<T, N> &&component_array) {
        auto const it = component_array.entity_to_index.find(entity);
        if (it != component_array.entity_to_index.end()) {
            component_array.components.at(it->second) = new_value;
            return std::make_pair(sts::error::ok, std::move(component_array));
        }
        return std::make_pair(sts::error::invalid_entity, component_array);
    }

    /**
     * @brief Retrieves the component associated with a specific entity from the given component array.
     *
     * This function attempts to find and return the component corresponding to the provided entity
     * within the component array. If the entity exists within the array, the associated component
     * is returned as an `std::optional<T>`. If the entity is not found, the function returns
     * `std::nullopt`.
     *
     * @tparam T The type of the component stored in the component array.
     * @tparam N The maximum number of components the component array can hold.
     * @param entity The entity for which the component is being retrieved.
     * @param component_array The array of components where each component is associated with an entity.
     * @return std::optional<T> The component associated with the entity if it exists, otherwise `std::nullopt`.
     */
    template<typename T, std::size_t N>
    std::optional<T> get_component(Entity entity, ComponentBase<T, N> const &component_array) {
        if (component_array.entity_to_index.contains(entity)) {
            return component_array.components.at(component_array.entity_to_index.at(entity));
        }
        return {};
    }

    /* Maybe use this for easier interaction */
    template<typename T, std::size_t N>
    T &get_component_reference(Entity entity, ComponentBase<T, N> &component_array) {
        if (component_array.entity_to_index.contains(entity)) {
            return component_array.components.at(component_array.entity_to_index.at(entity));
        }
        throw sts::CoreError(std::format("invalid entity {} for component type {}", entity, typeid(T).name()));
    }

    struct System {
        std::unordered_set<Entity> entities{};
    };

    template<typename Sys>
    std::pair<sts::error, Sys> add_to_system(Entity entity, Sys &&system) {
        static_assert(std::is_base_of_v<System, Sys>, "System base class mismatch");

        if (system.entities.find(entity) != system.entities.end()) {
            return std::make_pair(sts::error::entity_exists, std::move(system));
        }

        if (auto const itr = system.entities.insert(entity); !itr.second) {
            return std::make_pair(sts::error::failed, std::move(system));
        }
        return std::make_pair(sts::error::ok, std::move(system));
    }

    template<typename T_Sys>
    std::pair<sts::error, T_Sys> remove_from_system(Entity entity, T_Sys &&system) {
        static_assert(std::is_base_of_v<System, T_Sys>, "System base class mismatch");

        if (auto itr = system.entities.find(entity); itr != system.entities.end()) {
            system.entities.erase(itr);
            return std::make_pair(sts::error::ok, std::move(system));
        }
        return std::make_pair(sts::error::invalid_entity, std::move(system));
    }


} // namespace core
#endif // ENTITYCOMPONENTSYSTEM_HPP
