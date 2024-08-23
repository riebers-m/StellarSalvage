//
// Created by HP on 23.08.2024.
//

#include "core/EntityComponentSystem.hpp"
#include <stdexcept>
#include "Exception.hpp"

namespace core {
    using Entities = std::set<std::size_t>;
    // static Entities entities{};

    std::pair<Entity, Entities> create_entity(Entities entities, std::size_t max_entity_count) {
        try {
            if(entities.size() > max_entity_count) {
                throw sts::CoreError(std::format("Could not create entity, max entity count reached ({})", max_entity_count));
            }

            for(auto i=0;i<max_entity_count;i++) {
                if(!entities.contains(i)) {
                    if(auto const [itr, inserted] = entities.insert(i);inserted) {
                        return std::make_pair(i,entities);
                    }
                }
            }
            throw sts::CoreError(std::format("Could not create entity"));
        } catch(std::out_of_range const& e) {
            throw sts::CoreError(std::format("Entity out of range: {}", e.what()));
        }
    }
}