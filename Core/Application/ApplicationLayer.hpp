#pragma once

namespace gaps
{
	class IApplicationLayer
	{
	protected:
		virtual void OnStart() = 0;
		virtual void OnEnable() = 0;
		virtual void OnDisable() = 0;
		virtual void OnShow() = 0;
		virtual void OnHide() = 0;
		virtual void OnUpdate(float deltaTime) = 0;
		virtual void OnRender() = 0;
		virtual void OnRelease() = 0;
	};

	struct ApplicationLayerDescriptor final
	{
		bool bEnabled = true;
		bool bVisible = true;
	};

	class ApplicationLayer : public IApplicationLayer
	{
	public:
		explicit ApplicationLayer(ApplicationLayerDescriptor desc = {}) noexcept;

		virtual void Enable() final;
		virtual void Disable() final;
		virtual void Show() final;
		virtual void Hide() final;
		virtual void Release() final;

		virtual const ApplicationLayerDescriptor& GetDescriptor() const noexcept final;

	protected:
		void OnStart() override;
		void OnEnable() override;
		void OnDisable() override;
		void OnShow() override;
		void OnHide() override;
		void OnUpdate(float deltaTime) override;
		void OnRender() override;
		void OnRelease() override;

	private:
		virtual void Start() final;
		virtual void Update(float deltaTime) final;
		virtual void Render() final;

		ApplicationLayerDescriptor desc;

		friend class Engine;
	};
}