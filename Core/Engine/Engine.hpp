#pragma once

namespace gaps
{
	class Window;
	class Renderer;
	class ApplicationLayer;
	class EventDispatcher;

	class Engine final
	{
	public:
		Engine(std::function<ApplicationLayer* ()> InitCallback);
		~Engine();

		int32_t Start();

		Window* pWindow = nullptr;
		Renderer* pRenderer = nullptr;
		ApplicationLayer* pApplicationLayer = nullptr;
		EventDispatcher* pEventDispatcher = nullptr;

		inline static Engine* pInstance = nullptr;
	};
}