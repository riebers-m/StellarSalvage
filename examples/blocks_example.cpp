//
// Created by HP on 30.08.2024.
//
#include <any>
#include <random>
#include <ranges>
#include <spdlog/spdlog.h>
#include <utility>
#include "Engine.hpp"
#include "Exception.hpp"
#include "core/EntityComponentSystem.hpp"

auto constexpr entity_max_count = 2000;

struct Transform {
    core::Vector2D position{};
    core::Vector2D size{};
    core::Vector2D rotation{};
    float scale{1};
};

struct RigidBody {
    core::Vector2D velocity{};
    core::Vector2D acceleration{};
};

struct Gravity {
    core::Vector2D force{};
};

struct RenderColor {
    sts::Color color;
};

enum class COMPONENTS {
    transform,
    rigidbody,
    gravity,
    rendercolor,
};

struct Components {
    std::unordered_map<std::string, std::any> components;

    template<typename T, std::size_t N>
    std::pair<sts::error, core::ComponentBase<T, N> &&> get_component_ownership() {
        auto const type = typeid(T).name();

        if (auto it = components.find(type); it != components.end()) {
            //core::ComponentBase<T, N> component = std::any_cast<core::ComponentBase<T, N>>(it->second);

            // components.erase(it);
            return std::pair<sts::error, core::ComponentBase<T, N>>(sts::error::ok, it->second);
        }
        return std::make_pair(sts::error::invalid_component, core::ComponentBase<T, N>{});
    }

    template<typename T, std::size_t N>
    core::ComponentBase<T, N> get_component() {
        auto const type = typeid(T).name();
        if (components.contains(type)) {
            return std::any_cast<core::ComponentBase<T, N>>(components.at(type));
        }
        throw sts::CoreError(std::format("could not retrieve component array for type {}", type));
    }

    template<typename T, std::size_t N>
    sts::error add_component(core::ComponentBase<T, N> &&component) {
        auto const type = typeid(T).name();
        if (auto const it = components.find(type); it == components.end()) {
            components[type] = std::move(component);
            return sts::error::ok;
        }
        return sts::error::component_exists;
    }
};

class RenderSystem : public core::System {
public:
    static RenderSystem create_render_system(std::shared_ptr<sts::Renderer> renderer,
                                             std::vector<core::Entity> const &entities) {
        if (!renderer) {
            throw sts::CoreError("invalid renderer");
        }
        RenderSystem render_system{std::move(renderer)};
        for (auto const entity: entities) {
            render_system.entities.insert(entity);
        }
        return render_system;
    }

    explicit RenderSystem(std::shared_ptr<sts::Renderer> renderer_t) : renderer{std::move(renderer_t)} {}

    void draw(core::ComponentBase<Transform, entity_max_count> const &transform_components,
              core::ComponentBase<RenderColor, entity_max_count> const &rendercolor_components) {
        renderer->clear();

        for (auto const entity: entities) {

            auto transform = core::get_component(entity, transform_components);
            auto rendercolor = core::get_component(entity, rendercolor_components);
            if (!transform.has_value()) {
                spdlog::error(std::format("could not fetch transform component for {}", entity));
                continue;
            }
            if (!rendercolor.has_value()) {
                spdlog::error(std::format("could not fetch rendercolor component for {}", entity));
                continue;
            }

            renderer->draw_filled_rect(static_cast<int32_t>(transform.value().position.x),
                                       static_cast<int32_t>(transform.value().position.y),
                                       static_cast<int32_t>(transform.value().size.x),
                                       static_cast<int32_t>(transform.value().size.y), rendercolor.value().color);
        }
        renderer->present();
    }

private:
    std::shared_ptr<sts::Renderer> renderer;
};

void handle_events() {}

std::pair<Components, core::Entities> update(Components &&components, core::Entities &&entities) {
    static std::random_device rd;
    static std::mt19937 generator(rd());

    std::vector<core::Entity> living_entities;
    for (auto const entity: entities.living_entities) {
        living_entities.emplace_back(entity);
    }
    // remove random entity
    std::uniform_int_distribution<int> random_entity(0, static_cast<int>(living_entities.size()));
    auto const to_be_removed_entity = living_entities.at(random_entity(generator));
    auto [success, updated_entities] = core::destroy_entity(to_be_removed_entity, std::move(entities));
    if (success != sts::error::ok) {
        spdlog::error(std::format("removing entity {} failed", to_be_removed_entity));
        return std::make_pair(std::move(components), std::move(updated_entities));
    }
    // update transform
    {
        auto [success2, transforms] = components.get_component_ownership<Transform, entity_max_count>();
        if (success2 != sts::error::ok) {
            spdlog::error(std::format("retrieving transform for {} failed", to_be_removed_entity));
            return std::make_pair(std::move(components), std::move(updated_entities));
        }

        auto [success3, updated_transforms] = core::delete_component(to_be_removed_entity, std::move(transforms));
        if (success3 != sts::error::ok) {
            spdlog::error(std::format("removing transform for {} failed", to_be_removed_entity));
            return std::make_pair(std::move(components), std::move(updated_entities));
        }
        if (auto const success4 = components.add_component(std::move(updated_transforms)); success4 != sts::error::ok) {
            spdlog::error(std::format("adding updated transform failed"));
            return std::make_pair(std::move(components), std::move(updated_entities));
        }
    }
    // update rendercolor
    {
        auto [success2, rendercolors] = components.get_component_ownership<RenderColor, entity_max_count>();
        if (success2 != sts::error::ok) {
            spdlog::error(std::format("retrieving transform for {} failed", to_be_removed_entity));
            return std::make_pair(std::move(components), std::move(updated_entities));
        }

        auto [success3, updated_rendercolors] = core::delete_component(to_be_removed_entity, std::move(rendercolors));
        if (success3 != sts::error::ok) {
            spdlog::error(std::format("removing transform for {} failed", to_be_removed_entity));
            return std::make_pair(std::move(components), std::move(updated_entities));
        }
        if (auto const success4 = components.add_component(std::move(updated_rendercolors));
            success4 != sts::error::ok) {
            spdlog::error(std::format("adding updated transform failed"));
            return std::make_pair(std::move(components), std::move(updated_entities));
        }
    }
    spdlog::info(std::format("removed entity {} successfully", to_be_removed_entity));
    return std::make_pair(std::move(components), std::move(entities));
}


std::pair<Components, core::Entities> init() {
    std::random_device rd;
    std::mt19937 generator(rd());

    std::uniform_real_distribution<float> random_pos_x(0.0f, 1080.0f);
    std::uniform_real_distribution<float> random_pos_y(0.0f, 720.0f);
    std::uniform_int_distribution<int> random_color(0, static_cast<int>(sts::Color::COUNT) - 1);

    core::ComponentBase<Transform, entity_max_count> transform_components;
    core::ComponentBase<RigidBody, entity_max_count> rigidbody_components;
    core::ComponentBase<Gravity, entity_max_count> gravity_components;
    core::ComponentBase<RenderColor, entity_max_count> color_components;
    core::Entities entities;


    for (int i = 0; i < entity_max_count; i++) {
        auto [entity, new_entities] = core::create_entity(std::move(entities));
        entities = std::move(new_entities);
        auto [success, new_transform_components] =
                core::add_component(entity,
                                    Transform{core::Vector2D{random_pos_x(generator), random_pos_y(generator)},
                                              core::Vector2D{16, 16}, core::Vector2D{}, 1},
                                    std::move(transform_components));
        if (success != sts::error::ok) {
            spdlog::error(std::format("could not create transform component for {}", entity));
            exit(-1);
        }
        transform_components = std::move(new_transform_components);
        if (auto const color = sts::int_to_color(random_color(generator)); color.has_value()) {
            auto [success, new_color_components] =
                    core::add_component(entity, RenderColor{color.value()}, std::move(color_components));
            if (success != sts::error::ok) {
                spdlog::error(std::format("could not create color component for {}", entity));
                exit(-2);
            }
            color_components = std::move(new_color_components);
        }
    }
    Components components;
    components.add_component(std::move(transform_components));
    components.add_component(std::move(color_components));
    return std::make_pair(std::move(components), std::move(entities));
}

int main(int argc, char *argv[]) {
    try {

        auto [components, entities] = init();

        auto renderer = sts::Engine::create_renderer(1080, 720, "Stellar Salvage");
        if (!renderer) {
            spdlog::error("could not initialize renderer");
            return -1;
        }

        std::vector<core::Entity> entity_v;
        for (auto const &entity:
             std::views::keys(components.get_component<Transform, entity_max_count>().entity_to_index)) {
            entity_v.push_back(entity);
        }
        auto render_system = RenderSystem::create_render_system(std::move(renderer), entity_v);

        auto constexpr update_rate = std::chrono::milliseconds{1000 / 60};

        auto lastUpdateTime = std::chrono::system_clock::now();
        auto lastRenderTime = std::chrono::system_clock::now();

        auto framecount = 0;

        while (sts::Engine::is_window_open()) {
            auto constexpr max_updates = 5;
            auto updates = 0;
            auto now = std::chrono::system_clock::now();

            while (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTime) > update_rate &&
                   updates < max_updates) {
                handle_events();
                auto [updated_components, updated_entities] = update(std::move(components), std::move(entities));
                components = std::move(updated_components);
                entities = std::move(updated_entities);

                lastUpdateTime += update_rate;
                updates++;
                framecount++;
            }

            // if maybe an update tooks forever we dont want to catch up
            if (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTime) > update_rate) {
                lastUpdateTime = now - update_rate;
            }

            auto const rendercolor_components = components.get_component<RenderColor, entity_max_count>();
            auto const transform_components = components.get_component<Transform, entity_max_count>();
            render_system.draw(transform_components, rendercolor_components);

            lastRenderTime = now;

            while (std::chrono::duration_cast<std::chrono::milliseconds>(now - lastRenderTime) < update_rate &&
                   std::chrono::duration_cast<std::chrono::milliseconds>(now - lastUpdateTime) < update_rate) {
                std::this_thread::sleep_for(std::chrono::milliseconds{1});
                now = std::chrono::system_clock::now();
            }
        }
    } catch (sts::EngineError const &e) {
        spdlog::error(e.what());
    } catch (sts::CoreError const &e) {
        spdlog::error(e.what());
    }

    return 0;
}
