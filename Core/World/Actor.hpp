#pragma once

#include "../Event/EventHandler.hpp"

namespace gaps
{
	class IActor
	{
	public:
		virtual ~IActor() = default;

	protected:
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
	};

	class Actor : public IActor, public EventHandler
	{
	public:
		explicit Actor(bool bEnable = true);

		virtual void Enable() final;
		virtual void Disable() final;

		virtual bool IsEnabled() const final;

	protected:
		void OnEnable() override;
		void OnDisable() override;

	private:
		bool bEnabled = false;
	};
}