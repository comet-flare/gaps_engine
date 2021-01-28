#pragma once

namespace gaps
{
	class Window;
	class Renderer;

	class Engine final
	{
	public:
		Engine();
		~Engine();

		int32_t Start();

		Window* pWindow = nullptr;
		Renderer* pRenderer = nullptr;

		inline static Engine* pInstance = nullptr;
	};
}