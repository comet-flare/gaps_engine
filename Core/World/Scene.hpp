#pragma once

namespace gaps
{
	class Entity;

	class Scene final
	{
	public:
		using Registry = entt::registry;

		Entity CreateEntity(const std::string& name = std::string());
		Entity GetEntity(const std::string& name);
		void DestroyEntity(Entity entity);

		const Registry& GetRegistry() const noexcept;
		Entity GetPrimaryCamera();

	private:
		Registry registry;
		std::map<std::string, Entity> entities;

		inline static std::atomic_uint64_t entityCounter = 0;

		friend Entity;
	};
}