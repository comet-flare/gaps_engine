#pragma once

namespace gaps
{
	struct WindowDescriptor final
	{
		uint32_t width = 1920u;
		uint32_t height = 1080u;
		std::string title = "GAPS Engine";
	};

	class Window final
	{
	public:
		explicit Window(WindowDescriptor desc = {}) noexcept;

		int32_t Create();
		void Update();
		void Destroy();

		bool ShouldClose();
		void SwapBuffers();

		const WindowDescriptor& GetDescriptor() const noexcept;

	private:
		WindowDescriptor desc;
		GLFWwindow* pInternal = nullptr;

		friend class Engine;
	};
}