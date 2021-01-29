#include <gapspch.hpp>
#include <Core/Application/ApplicationLayer.hpp>

namespace gaps
{
	ApplicationLayer::ApplicationLayer(ApplicationLayerDescriptor desc) noexcept
		:
		desc{ std::move(desc) }
	{
	}

	void ApplicationLayer::Start()
	{
		OnStart();

		if (desc.bEnabled)
		{
			Enable();
		}

		if (desc.bVisible)
		{
			Show();
		}
	}

	void ApplicationLayer::Enable()
	{
		desc.bEnabled = true;
		OnEnable();
	}

	void ApplicationLayer::Disable()
	{
		desc.bEnabled = false;
		OnDisable();
	}

	void ApplicationLayer::Show()
	{
		desc.bVisible = true;
		OnShow();
	}

	void ApplicationLayer::Hide()
	{
		desc.bVisible = false;
		OnHide();
	}

	void ApplicationLayer::Update(float deltaTime)
	{
		if (desc.bEnabled)
		{
			OnUpdate(deltaTime);
		}
	}

	void ApplicationLayer::Render()
	{
		if (desc.bVisible)
		{
			OnRender();
		}
	}

	void ApplicationLayer::Release()
	{
		OnRelease();
	}

	const ApplicationLayerDescriptor& ApplicationLayer::GetDescriptor() const noexcept
	{
		return desc;
	}

	void ApplicationLayer::OnStart()
	{
	}

	void ApplicationLayer::OnEnable()
	{
	}

	void ApplicationLayer::OnDisable()
	{
	}

	void ApplicationLayer::OnShow()
	{
	}

	void ApplicationLayer::OnHide()
	{
	}

	void ApplicationLayer::OnUpdate(float deltaTime)
	{
	}

	void ApplicationLayer::OnRender()
	{
	}

	void ApplicationLayer::OnRelease()
	{
	}
}