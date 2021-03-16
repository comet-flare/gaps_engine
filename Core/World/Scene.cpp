#include <gapspch.hpp>
#include <Core/World/Entity.hpp>
#include <Core/World/Transform.hpp>
#include <Core/Render/Camera.hpp>

namespace gaps
{
    Entity Scene::CreateEntity(const std::string& name)
    {
        Entity entity = { registry.create(), this };
        entity.AddComponent<TransformComponent>();
        auto& nameComponent = entity.AddComponent<NameComponent>();
        nameComponent.name = name.empty() ? "Entity_" + std::to_string(entityCounter++) : name;
        entities[name] = entity;
        return entity;
    }

    Entity Scene::GetEntity(const std::string& name)
    {
        return entities[name];
    }

    void Scene::DestroyEntity(Entity entity)
    {
        auto it = entities.find(entity.GetComponent<NameComponent>().name);
        entities.erase(it);
        registry.destroy(entity);
    }

    const Scene::Registry& Scene::GetRegistry() const noexcept
    {
        return registry;
    }

    Entity Scene::GetPrimaryCamera()
    {
        auto view = registry.view<CameraComponent>();
        for (auto entity : view)
        {
            const auto& camera = view.get<CameraComponent>(entity);
            if (camera.primary)
            {
                return Entity{ entity, this };
            }
        }

        return {};
    }
}