#pragma once

namespace gaps
{
	class Window;
	class Renderer;
	class ApplicationLayer;

	class Engine final
	{
	public:
		Engine(ApplicationLayer* pApplicationLayer);
		~Engine();

		int32_t Start();

		Window* pWindow = nullptr;
		Renderer* pRenderer = nullptr;
		ApplicationLayer* pApplicationLayer = nullptr;

		inline static Engine* pInstance = nullptr;
	};
}