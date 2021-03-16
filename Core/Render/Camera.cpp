#include <gapspch.hpp>
#include <Core/Render/Camera.hpp>
#include <Core/Time/TickEvent.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/World/Entity.hpp>
#include <Core/World/Transform.hpp>
#include <Core/Render/Renderer.hpp>
#include <Core/Window/Window.hpp>

namespace gaps
{
    CameraSystem::CameraSystem()
    {
        TickHandler = [](const TickEvent& e) -> bool
        {
            auto cameraView = Engine::pScene->GetRegistry().view<
                const TransformComponent, const CameraComponent>();
            
            for (auto entity : cameraView)
            {
                auto& transform = cameraView.get<const TransformComponent>(entity);
                auto& camera = cameraView.get<const CameraComponent>(entity);

                if (camera.primary)
                {
                    Camera::projection = glm::perspective
                    (
                        glm::radians(camera.fov),
                        Engine::pWindow->GetAspectRatio(),
                        camera.zNear,
                        camera.zFar
                    );

                    Camera::view = glm::lookAt
                    (
                        transform.location,
                        transform.location + camera.front,
                        camera.up
                    );

                    break;
                }
            }

            return false;
        };
    }

    void Camera::UpdateVectors(CameraComponent& camera)
    {
        glm::vec3 front{ 0.f };
        front.x = cos(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
        front.y = sin(glm::radians(camera.pitch));
        front.z = sin(glm::radians(camera.yaw)) * cos(glm::radians(camera.pitch));
        camera.front = glm::normalize(front);
        camera.right = glm::normalize(glm::cross(camera.front, camera.worldUp));
        camera.up = glm::normalize(glm::cross(camera.right, camera.front));
    }

    void Camera::MoveForward(Entity camera, const float deltaTime)
    {
        const auto& cameraComponent = camera.GetComponent<CameraComponent>();
        auto& cameraTransform = camera.GetComponent<TransformComponent>();
        const float velocity = cameraComponent.speed * deltaTime;
        cameraTransform.location += cameraComponent.front * velocity;
    }

    void Camera::MoveBackward(Entity camera, const float deltaTime)
    {
        const auto& cameraComponent = camera.GetComponent<CameraComponent>();
        auto& cameraTransform = camera.GetComponent<TransformComponent>();
        const float velocity = cameraComponent.speed * deltaTime;
        cameraTransform.location -= cameraComponent.front * velocity;
    }

    void Camera::MoveLeft(Entity camera, const float deltaTime)
    {
        const auto& cameraComponent = camera.GetComponent<CameraComponent>();
        auto& cameraTransform = camera.GetComponent<TransformComponent>();
        const float velocity = cameraComponent.speed * deltaTime;
        cameraTransform.location -= cameraComponent.right * velocity;
    }

    void Camera::MoveRight(Entity camera, const float deltaTime)
    {
        const auto& cameraComponent = camera.GetComponent<CameraComponent>();
        auto& cameraTransform = camera.GetComponent<TransformComponent>();
        const float velocity = cameraComponent.speed * deltaTime;
        cameraTransform.location += cameraComponent.right * velocity;
    }

    void Camera::MoveUp(Entity camera, const float deltaTime)
    {
        const auto& cameraComponent = camera.GetComponent<CameraComponent>();
        auto& cameraTransform = camera.GetComponent<TransformComponent>();
        const float velocity = cameraComponent.speed * deltaTime;
        cameraTransform.location += cameraComponent.up * velocity;
    }

    void Camera::MoveDown(Entity camera, const float deltaTime)
    {
        const auto& cameraComponent = camera.GetComponent<CameraComponent>();
        auto& cameraTransform = camera.GetComponent<TransformComponent>();
        const float velocity = cameraComponent.speed * deltaTime;
        cameraTransform.location -= cameraComponent.up * velocity;
    }

    void Camera::Zoom(Entity camera, const float yOffset)
    {
        auto& cameraComponent = camera.GetComponent<CameraComponent>();
        cameraComponent.fov -= (float)yOffset;
        if (cameraComponent.fov < cameraComponent.minFov)
            cameraComponent.fov = cameraComponent.minFov;
        if (cameraComponent.fov > cameraComponent.maxFov)
            cameraComponent.fov = cameraComponent.maxFov;
    }

    void Camera::LookAround(Entity camera, float xOffset, float yOffset)
    {
        auto& cameraComponent = camera.GetComponent<CameraComponent>();
        xOffset *= cameraComponent.sensitivity;
        yOffset *= cameraComponent.sensitivity;
        cameraComponent.yaw += xOffset;
        cameraComponent.pitch += yOffset;
        if (cameraComponent.constrainPitch)
        {
            if (cameraComponent.pitch > 89.0f)
                cameraComponent.pitch = 89.0f;
            if (cameraComponent.pitch < -89.0f)
                cameraComponent.pitch = -89.0f;
        }
        UpdateVectors(cameraComponent);
    }
}