#pragma once

#include "Scene.hpp"
#include "../Debugger/Debug.hpp"

namespace gaps
{
	class Entity final
	{
	public:
		using Handle = entt::entity;

		Entity() = default;
		Entity(Handle handle, Scene* pScene);
		Entity(const Entity& other) = default;

		template<typename T, typename... Args>
		T& AddComponent(Args&&... args)
		{
			if (HasComponent<T>())
			{
				gaps::Debug::Crit(("Component is already in the registry"), "Core.World.Entity");
			}

			T& component = pScene->registry.emplace<T>(handle, std::forward<Args>(args)...);
			return component;
		}

		template<typename T>
		void RemoveComponent()
		{
			if (!HasComponent<T>())
			{
				gaps::Debug::Crit(("Component not found in the registry"), "Core.World.Entity");
			}

			pScene->registry.remove<T>(handle);
		}

		template<typename T>
		T& GetComponent()
		{
			if (!HasComponent<T>())
			{
				gaps::Debug::Crit(("Component not found in the registry"), "Core.World.Entity");
			}

			return pScene->registry.get<T>(handle);
		}

		template<typename T>
		bool HasComponent()
		{
			return pScene->registry.has<T>(handle);
		}

		explicit operator bool() const;
		operator Handle() const;
		operator uint32_t() const;

		bool operator==(const Entity& other) const;
		bool operator!=(const Entity& other) const;

	private:
		Handle handle{ entt::null };
		Scene* pScene = nullptr;
	};

	struct NameComponent final
	{
		std::string name = std::string();
	};
}