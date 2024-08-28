//
// Created by HP on 23.08.2024.
//
#include <catch2/catch_test_macros.hpp>
#include <unordered_set>
#include "core/EntityComponentSystem.hpp"

#include "Exception.hpp"

TEST_CASE("create_entity creates a new entity and updates the Entities struct correctly", "[entity_system]") {
    core::Entities entities;

    SECTION("Creating a new entity when there are no available entities") {
        auto [entity, updated_entities] = core::create_entity(std::move(entities));
        REQUIRE(entity == 0); // First entity should have ID 0
        REQUIRE(updated_entities.living_entities.size() == 1);
        REQUIRE(updated_entities.living_entities.count(entity) == 1);
        REQUIRE(updated_entities.totoal_entity_count == 1);
    }

    SECTION("Creating a second entity") {
        auto [entity1, updated_entities1] = create_entity(std::move(entities));
        auto [entity2, updated_entities2] = create_entity(std::move(updated_entities1));
        REQUIRE(entity2 == 1); // Second entity should have ID 1
        REQUIRE(updated_entities2.living_entities.size() == 2);
        REQUIRE(updated_entities2.living_entities.count(entity2) == 1);
        REQUIRE(updated_entities2.totoal_entity_count == 2);
    }

    SECTION("Reusing an available entity") {
        auto [entity1, updated_entities1] = create_entity(std::move(entities));
        auto [destroyed, updated_entities2] = destroy_entity(entity1, std::move(updated_entities1));
        auto [entity2, updated_entities3] = create_entity(std::move(updated_entities2));
        REQUIRE(entity2 == entity1); // Should reuse the first entity ID
        REQUIRE(updated_entities3.living_entities.size() == 1);
        REQUIRE(updated_entities3.living_entities.count(entity2) == 1);
    }
}

TEST_CASE("destroy_entity removes an existing entity and makes it available for reuse", "[entity_system]") {
    core::Entities entities;
    auto [entity, updated_entities] = create_entity(std::move(entities));

    SECTION("Destroying an existing entity") {
        auto [error, updated_entities_after_destroy] = destroy_entity(entity, std::move(updated_entities));
        REQUIRE(error == sts::error::ok);
        REQUIRE(updated_entities_after_destroy.living_entities.empty());
        REQUIRE(updated_entities_after_destroy.available_entities.size() == 1);
        REQUIRE(updated_entities_after_destroy.available_entities.front() == entity);
    }

    SECTION("Destroying a non-existing entity") {
        auto [entity, updated_entities] = create_entity(std::move(entities));
        core::Entity non_existent_entity = entity + 1; // Make sure this entity ID is not created yet
        auto [error, updated_entities_after_destroy] = destroy_entity(non_existent_entity, std::move(updated_entities));
        REQUIRE(error == sts::error::invalid_entity);
        REQUIRE(updated_entities_after_destroy.living_entities.size() == 1);
    }

    SECTION("Creating and destroying multiple entities") {
        auto [entity1, updated_entities1] = create_entity(std::move(updated_entities));
        auto [entity2, updated_entities2] = create_entity(std::move(updated_entities1));
        auto [destroyed1, updated_entities3] = destroy_entity(entity1, std::move(updated_entities2));
        auto [destroyed2, updated_entities4] = destroy_entity(entity2, std::move(updated_entities3));
        REQUIRE(destroyed1 == sts::error::ok);
        REQUIRE(destroyed2 == sts::error::ok);
        REQUIRE(updated_entities4.living_entities.size() == 1);
        REQUIRE(updated_entities4.available_entities.size() == 2);
    }
}

TEST_CASE("add component function tests", "[add_component]") {
    struct MockComponent {
        int a{};
        int b{};
    };

    core::ComponentBase<MockComponent, 1024> mock_components;

    SECTION("Try to add component") {
        auto const [success, new_component] = core::add_component(0, MockComponent{1,2}, std::move(mock_components));
        REQUIRE(success == sts::error::ok);
        REQUIRE(new_component.components.at(0).a == 1);
        REQUIRE(new_component.components.at(0).b == 2);
    }
}

TEST_CASE("delete_component removes an existing entity and maintains component array integrity", "[component_system]") {
    struct MockComponent {
        int a{};
        int b{};
    };

    core::ComponentBase<MockComponent, 5> component_array;

    for(int i=0;i<5;i++) {
        auto [success, new_component_array] = core::add_component(i, MockComponent{i,i}, std::move(component_array));
        component_array = std::move(new_component_array);
    }

    SECTION("Successfully delete an existing entity") {
        auto [result, updated_component_array] = delete_component(2, std::move(component_array));
        REQUIRE(result == sts::error::ok);
        REQUIRE(updated_component_array.entity_count == 4);
        REQUIRE(updated_component_array.entity_to_index.at(4) == 2);
        REQUIRE(updated_component_array.index_to_entity.at(2) == 4);
        REQUIRE(updated_component_array.components[2].a == 4);
        REQUIRE(updated_component_array.components[2].b == 4);
    }

    SECTION("Delete last entity in the array") {
        auto [result, updated_component_array] = delete_component(4, std::move(component_array));
        REQUIRE(result == sts::error::ok);
        REQUIRE(updated_component_array.entity_count == 4);
        REQUIRE(updated_component_array.components[3].a == 3);
        REQUIRE(updated_component_array.components[3].b == 3);
    }

    SECTION("Attempt to delete a non-existent entity") {
        core::Entity non_existent_entity = 5;
        auto [result, updated_component_array] = delete_component(non_existent_entity, std::move(component_array));
        REQUIRE(result == sts::error::invalid_entity);
        REQUIRE(updated_component_array.entity_count == 5); // No change in entity count
    }
}

TEST_CASE("delete_component handles empty component arrays correctly", "[component_system]") {
    core::ComponentBase<int, 5> component_array;

    SECTION("Attempt to delete from an empty array") {
        core::Entity non_existent_entity = 1;
        auto [result, updated_component_array] = delete_component(non_existent_entity, std::move(component_array));
        REQUIRE(result == sts::error::invalid_entity);
        REQUIRE(updated_component_array.entity_count == 0); // No change in entity count
        REQUIRE(updated_component_array.entity_to_index.empty()); // Maps should remain empty
        REQUIRE(updated_component_array.index_to_entity.empty());
    }
}