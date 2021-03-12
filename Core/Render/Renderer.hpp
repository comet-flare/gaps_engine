#pragma once

#include "../World/Actor.hpp"
#include "../Window/WindowEvent.hpp"

namespace gaps
{
	class RenderSystem;

	struct RendererDescriptor final
	{
		glm::vec4 clearColor{ 0.2f, 0.28f, 0.36f, 1.f };
	};

	class Renderer final : public EventHandler
	{
	public:
		explicit Renderer(const RendererDescriptor& desc = {}) noexcept;
		~Renderer() override;

		void Setup();
		void ClearScreen();

		const RendererDescriptor& GetRendererDescriptor() const noexcept;

		//// TODO. remove
		std::vector<class Shader*> shaders = {};
		////

	private:
		bool HandleWindow(const WindowEvent& e);

		RendererDescriptor desc;
		RenderSystem* pSystem = nullptr;
	};

	class RenderSystem : public Actor
	{
	private:
		explicit RenderSystem(Renderer* pRenderer);

		friend Renderer;
	};
}