#include <gapspch.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Render/Renderer.hpp>
#include <Core/Application/ApplicationLayer.hpp>
#include <Core/Debugger/Debug.hpp>
#include <Core/Event/EventDispatcher.hpp>
#include <Core/Event/InternalEvents.hpp>
#include <Core/Input/Input.hpp>
#include <Core/Time/TickEvent.hpp>

MOD("Core.Engine");

namespace gaps
{
	int32_t Engine::Run(std::function<ApplicationLayer* ()> InitCallback)
	{
		pEventDispatcher = new EventDispatcher();
		pWindow = new Window();
		pRenderer = new Renderer();
		pApplicationLayer = InitCallback();

#ifdef _DEBUG
		Debug::Enable();
#endif

		// Initialize GLFW Library
		if (!glfwInit())
		{
			DEBUG_CRIT("Failed to initialize GLFW library!");
			Release();
			return EXIT_FAILURE;
		}

		pWindow->Create();

		// Initialize GLAD
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			DEBUG_CRIT("Failed to initialize GLAD!");
			Release();
			return EXIT_FAILURE;
		}

		InternalEvents::Register(pWindow->pInternal);
		Input::RegisterDevices();

		pRenderer->Setup();
		pApplicationLayer->Start();

		while (!pWindow->ShouldClose())
		{
			Update();

			pRenderer->ClearScreen();
			pApplicationLayer->Render();
			pWindow->SwapBuffers();
		}

		Release();
		return EXIT_SUCCESS;
	}

	float Engine::GetElapsedSeconds()
	{
		return glfwGetTime();
	}

	void Engine::Update()
	{
		using namespace std::chrono;

		pEventDispatcher->DispatchEvents();

		const steady_clock::time_point currentTime = steady_clock::now();
		duration<int64_t, std::nano> diff = currentTime - previousTime;

		if (diff > std::chrono::milliseconds(1))
		{
			if (const auto newDiff = milliseconds(static_cast<int64_t>(1000.f / 24.f)); diff > newDiff)
			{
				diff = newDiff;
			}

			previousTime = currentTime;
			const float deltaTime = duration_cast<microseconds>(diff).count() / 1000000.f;

			pApplicationLayer->Update(deltaTime);

			auto pTickEvent = std::make_unique<TickEvent>(EventId::Tick);
			pTickEvent->args.deltaTime = deltaTime;
			pEventDispatcher->DispatchEvent(std::move(pTickEvent));
		}

		Input::Update();
		pWindow->Update();
	}

	void Engine::Release()
	{
		pApplicationLayer->Release();
		Input::ReleaseDevices();
		pWindow->Destroy();

		SAFE_RELEASE(pApplicationLayer);
		SAFE_RELEASE(pRenderer);
		SAFE_RELEASE(pWindow);
		SAFE_RELEASE(pEventDispatcher);
	}
}