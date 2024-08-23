//
// Created by HP on 23.08.2024.
//
#include <catch2/catch_test_macros.hpp>
#include <unordered_set>
#include "core/EntityComponentSystem.hpp"

#include "Exception.hpp"

TEST_CASE("create_entity function tests", "[create_entity]") {

    SECTION("Basic Entity Creation") {
        core::Entities entities;

        // Attempt to create an entity
        auto [newEntity, updatedEntities] = core::create_entity(entities);

        // Check if a new entity was created
        REQUIRE(updatedEntities.size() == 1);

        // Check if the new entity is in the set
        REQUIRE(updatedEntities.find(newEntity) != updatedEntities.end());
    }

    SECTION("Multiple Entity Creation within max limit") {
        core::Entities entities;

        std::size_t numEntitiesToCreate = 5;
        std::size_t maxEntityCount = 10;

        // Create multiple entities within the limit
        for (std::size_t i = 0; i < numEntitiesToCreate; ++i) {
            auto [newEntity, updatedEntities] = core::create_entity(entities, maxEntityCount);
            entities = updatedEntities;  // Update entities for the next iteration
        }

        // Check if the correct number of entities was created
        REQUIRE(entities.size() == numEntitiesToCreate);
    }

    SECTION("Maximum Entity Count") {
        core::Entities entities;

        std::size_t maxEntityCount = 3;

        // Create up to the maximum number of entities
        for (std::size_t i = 0; i < maxEntityCount; ++i) {
            auto [newEntity, updatedEntities] = core::create_entity(entities, maxEntityCount);
            entities = updatedEntities;  // Update entities for the next iteration
        }

        // Check that no more entities can be created
        REQUIRE_THROWS_AS(core::create_entity(entities, maxEntityCount), sts::CoreError);
    }

    SECTION("Boundary Condition: Creating exactly max_entity_count entities") {
        core::Entities entities;

        std::size_t maxEntityCount = 5;

        // Create exactly maxEntityCount entities
        for (std::size_t i = 0; i < maxEntityCount; ++i) {
            auto [newEntity, updatedEntities] = core::create_entity(entities, maxEntityCount);
            entities = updatedEntities;  // Update entities for the next iteration
        }

        // Check if the set contains exactly maxEntityCount entities
        REQUIRE(entities.size() == maxEntityCount);

        // Ensure trying to create one more entity throws an error
        REQUIRE_THROWS_AS(core::create_entity(entities, maxEntityCount), sts::CoreError);
    }
}