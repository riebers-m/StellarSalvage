//
// Created by HP on 02.09.2024.
//
#include "core/EnteiComponentSystem.hpp"

namespace core {
    Entity EntityManager::create_new_entity() {
        Entity new_entity;
        if (!m_available_entities.empty()) {
            new_entity = m_available_entities.front();
            m_available_entities.pop();
        } else {
            new_entity = m_total_entity_count++;
        }
        m_living_entities.insert(new_entity);
        return new_entity;
    }

    sts::error EntityManager::destroy_entity(Entity entity) {
        if (auto itr = m_living_entities.find(entity); itr != m_living_entities.end()) {
            m_available_entities.push(*itr);
            m_living_entities.erase(itr);
            return sts::error::ok;
        }
        return sts::error::invalid_entity;
    }


}