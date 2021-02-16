#pragma once

#include "../Event/EventHandler.hpp"
#include "../Window/WindowEvent.hpp"

namespace gaps
{
	struct RendererDescriptor final
	{
		glm::vec4 clearColor{ 0.2f, 0.28f, 0.36f, 1.f };
	};

	class Renderer final : public EventHandler
	{
	public:
		explicit Renderer(RendererDescriptor desc = {}) noexcept;
		~Renderer();

		void Setup();
		void ClearScreen();

		const RendererDescriptor& GetRendererDescriptor() const noexcept;

	private:
		bool HandleWindow(WindowEvent e);

		RendererDescriptor desc;
	};
}