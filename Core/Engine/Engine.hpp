#pragma once

namespace gaps
{
	class Window;

	class Engine final
	{
	public:
		Engine();
		~Engine();

		int32_t Start();

		Window* pWindow = nullptr;

		inline static Engine* pInstance = nullptr;
	};
}