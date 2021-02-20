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
		static int32_t Run(std::function<ApplicationLayer* ()> InitCallback);

		inline static Window* pWindow = nullptr;
		inline static Renderer* pRenderer = nullptr;
		inline static ApplicationLayer* pApplicationLayer = nullptr;
		inline static EventDispatcher* pEventDispatcher = nullptr;

	private:
		static void Release();
	};
}