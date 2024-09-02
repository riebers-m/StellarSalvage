//
// Created by HP on 23.08.2024.
//

#include "core/EntityComponentSystem.hpp"
#include "Exception.hpp"

namespace core {
    std::pair<Entity, Entities> create_entity(Entities &&entities) noexcept {
        Entity new_entity;
        if (!entities.available_entities.empty()) {
            new_entity = entities.available_entities.front();
            entities.available_entities.pop();
        } else {
            new_entity = entities.total_entity_count++;
        }
        entities.living_entities.insert(new_entity);
        return std::make_pair(new_entity, std::move(entities));
    }

    std::pair<sts::error, Entities> destroy_entity(Entity entity, Entities &&entities) noexcept {
        if (auto itr = entities.living_entities.find(entity); itr != entities.living_entities.end()) {
            entities.available_entities.push(*itr);
            entities.living_entities.erase(itr);
            return std::make_pair(sts::error::ok, std::move(entities));
        }
        return std::make_pair(sts::error::invalid_entity, std::move(entities));
    }
} // namespace core
