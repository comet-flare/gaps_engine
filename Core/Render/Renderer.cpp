#include <gapspch.hpp>
#include <Core/Render/Renderer.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/World/Entity.hpp>
#include <Core/World/Transform.hpp>
#include <Core/Render/Shader.hpp>
#include <Core/Time/TickEvent.hpp>

namespace gaps
{
	Renderer::Renderer(const RendererDescriptor& desc) noexcept
		:
		desc{ desc },
		pSystem{ new RenderSystem(this) }
	{
		WindowHandler = BIND_EVENT(Renderer::HandleWindow);
		StartListening();
	}

	Renderer::~Renderer()
	{
		StopListening();
		SAFE_RELEASE(pSystem);
	}

	void Renderer::Setup()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void Renderer::ClearScreen()
	{
		glClearColor
		(
			desc.clearColor.r,
			desc.clearColor.g,
			desc.clearColor.b,
			desc.clearColor.a
		);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	const RendererDescriptor& Renderer::GetRendererDescriptor() const noexcept
	{
		return desc;
	}

	bool Renderer::HandleWindow(const WindowEvent& e)
	{
		switch (e.GetId())
		{
		case EventId::WindowSizeChange:
			glViewport
			(
				0,
				0,
				static_cast<GLsizei>(e.args.width),
				static_cast<GLsizei>(e.args.height)
			);
			break;
		default:
			break;
		}

		return false;
	}

	RenderSystem::RenderSystem(Renderer* pRenderer)
	{
		TickHandler = [pRenderer](const TickEvent& e) -> bool
		{
			auto modelView = Engine::pScene->GetRegistry().view<const TransformComponent>();
			for (auto entity : modelView)
			{
				auto& transform = modelView.get<const TransformComponent>(entity);

				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, transform.location);
				model = glm::rotate(model, transform.rotation.x, glm::vec3(1.f, 0.f, 0.f));
				model = glm::rotate(model, transform.rotation.y, glm::vec3(0.f, 1.f, 0.f));
				model = glm::rotate(model, transform.rotation.z, glm::vec3(0.f, 0.f, 1.f));
				model = glm::scale(model, transform.scale);

				for (const auto& pShader : pRenderer->shaders)
				{
					pShader->SetUniform("uTransform", model);
				}
			}

			return false;
		};
	}
}