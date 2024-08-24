//
// Created by HP on 23.08.2024.
//

#ifndef ENTITYCOMPONENTSYSTEM_HPP
#define ENTITYCOMPONENTSYSTEM_HPP
#include <set>
namespace core {
    using Entity = std::size_t;
    using Entities = std::set<Entity>;

    /**
     * @brief Creates a new Entity and adds it to the collection of existing entities.
     *
     * This function attempts to create a new Entity and add it to the provided collection of entities.
     * The function returns a `std::pair` containing the newly created Entity and the updated collection.
     *
     * @param entities A collection of existing entities to which the new Entity will be added.
     *                 The type of this collection is `Entities`, which is typically a container like `std::set<Entity>`
     * or `std::vector<Entity>`.
     * @param max_entity_count The maximum number of entities allowed in the collection.
     *                         If the number of entities reaches this limit, the function may throw an exception.
     *                         The default value is 1000.
     * @return std::pair<Entity, Entities> A pair consisting of:
     *         - The newly created `Entity`.
     *         - The updated collection of entities including the newly created `Entity`.
     * @throws sts::CoreError If the current number of entities has reached `max_entity_count`
     */
    std::pair<Entity, Entities> create_entity(Entities, std::size_t max_entity_count = 1000);

    std::pair<bool, Entities> delete_entity(Entities, Entity);

} // namespace core
#endif // ENTITYCOMPONENTSYSTEM_HPP
