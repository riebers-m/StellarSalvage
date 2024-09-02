//
// Created by HP on 02.09.2024.
//

#include <catch2/catch_test_macros.hpp>
#include "core/EnteiComponentSystem.hpp"

TEST_CASE("EntityManager can create and destroy entities", "[EntityManager]") {
    core::EntityManager manager = core::EntityManager::create_entity_manager();

    SECTION("Creating new entities") {
        core::Entity entity1 = manager.create_new_entity();
        core::Entity entity2 = manager.create_new_entity();

        // Assuming entity1 and entity2 should be different
        REQUIRE(entity1 != entity2);
    }

    SECTION("Destroying entities") {
        core::Entity entity1 = manager.create_new_entity();
        core::Entity entity2 = manager.create_new_entity();

        // Destroy entity1
        auto result = manager.destroy_entity(entity1);
        REQUIRE(result == sts::error::ok); // Assuming sts::success is the success code

        // Trying to destroy entity1 again should return an error
        result = manager.destroy_entity(entity1);
        REQUIRE(result == sts::error::invalid_entity); // Assuming sts::error_entity_not_found is the error code for
                                                       // non-existent entities
    }

    SECTION("Reusing destroyed entity IDs") {
        core::Entity entity1 = manager.create_new_entity();
        core::Entity entity2 = manager.create_new_entity();

        // Destroy entity1
        manager.destroy_entity(entity1);

        // Create a new entity, which should reuse the ID of the destroyed entity
        core::Entity entity3 = manager.create_new_entity();
        REQUIRE(entity3 == entity1); // Assuming IDs are reused
    }

    SECTION("Destroying non-existent entities") {
        core::Entity fake_entity = 9999; // An entity ID that doesn't exist
        auto result = manager.destroy_entity(fake_entity);
        REQUIRE(result == sts::error::invalid_entity); // Assuming sts::error_entity_not_found is the error code for
                                                       // non-existent entities
    }
}

// Dummy struct to use as a component type in the tests
struct TestComponent {
    int value;
};

TEST_CASE("Component class template functionality", "[Component]") {
    core::Component<TestComponent> componentManager;

    SECTION("Adding components") {
        core::Entity entity1 = 1;
        core::Entity entity2 = 2;

        TestComponent comp1{10};
        TestComponent comp2{20};

        // Add components to the entities
        auto result = componentManager.add_component(entity1, comp1);
        REQUIRE(result == sts::error::ok);

        result = componentManager.add_component(entity2, comp2);
        REQUIRE(result == sts::error::ok);

        // Trying to add a component to the same entity should return an error
        result = componentManager.add_component(entity1, comp1);
        REQUIRE(result == sts::error::entity_exists);
    }

    SECTION("Retrieving components") {
        core::Entity entity = 1;
        TestComponent comp{10};
        componentManager.add_component(entity, comp);

        // Retrieve the component
        TestComponent retrievedComp = componentManager.get(entity);
        REQUIRE(retrievedComp.value == comp.value);

        // Attempting to retrieve a component from a non-existent entity should throw an exception
        core::Entity nonExistentEntity = 9999;
        REQUIRE_THROWS_AS(componentManager.get(nonExistentEntity), sts::CoreError);
    }

    SECTION("Removing components") {
        core::Entity entity1 = 1;
        core::Entity entity2 = 2;

        TestComponent comp1{10};
        TestComponent comp2{20};

        componentManager.add_component(entity1, comp1);
        componentManager.add_component(entity2, comp2);

        // Remove a component
        auto result = componentManager.remove_component(entity1);
        REQUIRE(result == sts::error::ok);

        // Trying to remove the same component again should return an error
        result = componentManager.remove_component(entity1);
        REQUIRE(result == sts::error::invalid_entity);

        // The removed component should no longer be retrievable
        REQUIRE_THROWS_AS(componentManager.get(entity1), sts::CoreError);
    }

    SECTION("Entity limit handling") {
        for (std::size_t i = 0; i < core::ENTITY_COUNT; ++i) {
            REQUIRE(componentManager.add_component(i, TestComponent{static_cast<int>(i)}) == sts::error::ok);
        }

        // Adding one more component beyond the limit should return an error
        REQUIRE(componentManager.add_component(core::ENTITY_COUNT, TestComponent{static_cast<int>(core::ENTITY_COUNT)}) ==
                sts::error::entity_limit);
    }
}

TEST_CASE("ComponentManager class functionality", "[ComponentManager]") {
    core::ComponentManager manager;

    SECTION("Adding components to entities") {
        core::Entity entity1 = 1;
        TestComponent comp1{10};

        // Add component to entity1
        auto result = manager.add_to_component(entity1, comp1);
        REQUIRE(result == sts::error::ok);

        // Attempt to add the same component to the same entity should return an error
        result = manager.add_to_component(entity1, comp1);
        REQUIRE(result == sts::error::entity_exists);
    }

    SECTION("Removing components from entities") {
        core::Entity entity1 = 1;
        TestComponent comp1{10};
        manager.add_to_component(entity1, comp1);

        // Remove the component from entity1
        auto result = manager.remove_from_component<TestComponent>(entity1);
        REQUIRE(result == sts::error::ok);

        // Trying to remove a component from an entity that doesn't have it should return an error
        result = manager.remove_from_component<TestComponent>(entity1);
        REQUIRE(result == sts::error::invalid_entity);
    }

    SECTION("Retrieving components from entities") {
        core::Entity entity1 = 1;
        TestComponent comp1{10};
        manager.add_to_component(entity1, comp1);

        // Retrieve the component from entity1
        auto& retrievedComp = manager.get_component<TestComponent>(entity1);
        REQUIRE(retrievedComp.value == comp1.value);

        // Attempting to retrieve a component from a non-existent entity should throw an exception
        core::Entity nonExistentEntity = 9999;
        REQUIRE_THROWS_AS(manager.get_component<TestComponent>(nonExistentEntity), sts::CoreError);
    }

    SECTION("Destroying an entity and its components") {
        core::Entity entity1 = 1;
        TestComponent comp1{10};
        manager.add_to_component(entity1, comp1);

        // Destroy entity1
        auto result = manager.destroy_entity(entity1);
        REQUIRE(result == sts::error::ok);

        // After destruction, attempting to retrieve the component should throw an exception
        REQUIRE_THROWS_AS(manager.get_component<TestComponent>(entity1), sts::CoreError);
    }

    SECTION("Handling missing component types") {
        core::Entity entity1 = 1;
        TestComponent comp1{10};

        // Attempt to remove a component from a type that was never added should return an error
        auto result = manager.remove_from_component<TestComponent>(entity1);
        REQUIRE(result == sts::error::invalid_component);

        // Attempt to retrieve a component from a type that was never added should throw an exception
        REQUIRE_THROWS_AS(manager.get_component<TestComponent>(entity1), sts::CoreError);
    }

    SECTION("Updating component values") {
        core::Entity entity1 = 1;
        TestComponent comp1{10};

        // Add component to entity1
        manager.add_to_component(entity1, comp1);

        // Update the component value
        auto& retrievedComp = manager.get_component<TestComponent>(entity1);
        retrievedComp.value = 20;

        // Retrieve the component again and check if the value has been updated
        auto const updatedComp = manager.get_component<TestComponent>(entity1);
        REQUIRE(updatedComp.value == 20);
    }
}
