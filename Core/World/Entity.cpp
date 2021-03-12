#include <gapspch.hpp>
#include <Core/World/Entity.hpp>

namespace gaps
{
    Entity::Entity(Handle handle, Scene* pScene)
        :
        handle{ handle },
        pScene{ pScene }
    {
    }

    Entity::operator bool() const
    {
        return handle != entt::null;
    }

    Entity::operator Handle() const
    {
        return handle;
    }

    Entity::operator uint32_t() const
    {
        return static_cast<uint32_t>(handle);
    }

    bool Entity::operator==(const Entity& other) const
    {
        return handle == other.handle && pScene == other.pScene;
    }

    bool Entity::operator!=(const Entity& other) const
    {
        return handle != other.handle || pScene != other.pScene;
    }
}