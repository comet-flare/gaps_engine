#include <gapspch.hpp>
#include <Core/Render/Renderer.hpp>

namespace gaps
{
	Renderer::Renderer(RendererDescriptor desc) noexcept
		:
		desc{ std::move(desc) }
	{
		WindowHandler = BIND_EVENT(Renderer::HandleWindow);
		StartListening();
	}

	Renderer::~Renderer()
	{
		StopListening();
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

	bool Renderer::HandleWindow(WindowEvent e)
	{
		switch (e.GetId())
		{
		case EventId::WindowSizeChange:
			glViewport(0, 0, e.args.width, e.args.height);
			break;
		default:
			break;
		}

		return false;
	}
}