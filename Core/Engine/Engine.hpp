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

		static float GetElapsedSeconds();

		inline static Window* pWindow = nullptr;
		inline static Renderer* pRenderer = nullptr;
		inline static ApplicationLayer* pApplicationLayer = nullptr;
		inline static EventDispatcher* pEventDispatcher = nullptr;

	private:
		static void Update();
		static void Release();

		inline static std::chrono::steady_clock::time_point previousTime;
	};
}