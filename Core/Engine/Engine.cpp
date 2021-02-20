#include <gapspch.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/Window/Window.hpp>
#include <Core/Render/Renderer.hpp>
#include <Core/Application/ApplicationLayer.hpp>
#include <Core/Debugger/Debug.hpp>
#include <Core/Event/EventDispatcher.hpp>
#include <Core/Event/InternalEvents.hpp>

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

		pRenderer->Setup();
		pApplicationLayer->Start();

		while (!pWindow->ShouldClose())
		{
			// First Stage
			pEventDispatcher->DispatchEvents();
			pWindow->Update();

			// Second Stage
			pApplicationLayer->Update(0.f);

			// Third Stage
			pRenderer->ClearScreen();
			pApplicationLayer->Render();
			pWindow->SwapBuffers();
		}

		pApplicationLayer->Release();
		pWindow->Destroy();

		Release();
		return EXIT_SUCCESS;
	}

	void Engine::Release()
	{
		SAFE_RELEASE(pApplicationLayer);
		SAFE_RELEASE(pRenderer);
		SAFE_RELEASE(pWindow);
		SAFE_RELEASE(pEventDispatcher);
	}
}