#include <gapspch.hpp>
#include <Core/Render/Renderer.hpp>

namespace gaps
{
	Renderer::Renderer(RendererDescriptor desc) noexcept
		:
		desc{ std::move(desc) }
	{
	}

	void Renderer::Setup()
	{
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

}