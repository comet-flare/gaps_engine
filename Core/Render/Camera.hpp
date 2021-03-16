#pragma once

#include "../World/Actor.hpp"

namespace gaps
{
	class RenderSystem;
	class Entity;

	struct CameraComponent final
	{
		glm::vec3 front{ 0.f, 0.f, -1.f };
		glm::vec3 up{ 0.f, 1.f, 0.f };
		glm::vec3 right{ 0.f, 0.f, 0.f };
		glm::vec3 worldUp{ 0.f, 1.f, 0.f };
		float yaw = -90.f;
		float pitch = 0.f;
		float speed = 3.f;
		float sensitivity = 0.1f;
		float fov = 45.f;
		float minFov = 1.f;
		float maxFov = 90.f;
		float zNear = 0.01f;
		float zFar = 10000.f;
		bool constrainPitch = true;
		bool primary = true; // todo. remove from here
	};

	class CameraSystem final : public Actor
	{
	public:
		CameraSystem();
	};

	class Camera final
	{
	public:
		static void UpdateVectors(CameraComponent& camera);
		static void MoveForward(Entity camera, float deltaTime);
		static void MoveBackward(Entity camera, float deltaTime);
		static void MoveLeft(Entity camera, float deltaTime);
		static void MoveRight(Entity camera, float deltaTime);
		static void MoveUp(Entity camera, float deltaTime);
		static void MoveDown(Entity camera, float deltaTime);
		static void Zoom(Entity camera, float yOffset);
		static void LookAround(Entity camera, float xOffset, float yOffset);

	private:
		inline static glm::mat4 view{ 1.f };
		inline static glm::mat4 projection{ 1.f };

		friend CameraSystem;
		friend RenderSystem;
	};
}