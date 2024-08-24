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

TEST_CASE("delete_entity function tests", "[delete_entity]") {

    SECTION("Successful Deletion") {
        core::Entities entities = { core::Entity{1}, core::Entity{2}, core::Entity{3} };

        // Attempt to delete an existing entity
        auto const entityToDelete = core::Entity{2};
        auto [success, updatedEntities] = core::delete_entity(entities, entityToDelete);

        // Check if the deletion was successful
        REQUIRE(success == true);

        // Ensure the entity was removed from the set
        REQUIRE(updatedEntities.find(entityToDelete) == updatedEntities.end());

        // Ensure the size of the collection has decreased
        REQUIRE(updatedEntities.size() == 2);
    }

    SECTION("Entity Not Found") {
        core::Entities entities = { core::Entity{1}, core::Entity{2}, core::Entity{3} };

        // Attempt to delete an entity that doesn't exist
        auto const entityToDelete = core::Entity{4};  // Entity 4 is not in the set
        auto [success, updatedEntities] = core::delete_entity(entities, entityToDelete);

        // Check if the deletion was unsuccessful
        REQUIRE(success == false);

        // Ensure the original collection remains unchanged
        REQUIRE(updatedEntities.size() == entities.size());
        REQUIRE(updatedEntities == entities);
    }

    SECTION("Deletion from Empty Collection") {
        core::Entities entities;  // Empty collection

        // Attempt to delete an entity from an empty collection
        auto const entityToDelete = core::Entity{1};
        auto [success, updatedEntities] = core::delete_entity(entities, entityToDelete);

        // Check if the deletion was unsuccessful
        REQUIRE(success == false);

        // Ensure the collection is still empty
        REQUIRE(updatedEntities.empty() == true);
    }
}