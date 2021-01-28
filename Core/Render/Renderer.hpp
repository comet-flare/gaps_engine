#pragma once

namespace gaps
{
	struct RendererDescriptor final
	{
		glm::vec4 clearColor{ 0.2f, 0.28f, 0.36f, 1.f };
	};

	class Renderer final
	{
	public:
		explicit Renderer(RendererDescriptor desc = {}) noexcept;

		void Setup();
		void ClearScreen();

		const RendererDescriptor& GetRendererDescriptor() const noexcept;

	private:
		RendererDescriptor desc;
	};
}