#include <gapspch.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/System/Window.hpp>
#include <Core/Render/Renderer.hpp>
#include <Core/Application/ApplicationLayer.hpp>

namespace gaps
{
	Engine::Engine(ApplicationLayer* pApplicationLayer)
		:
		pApplicationLayer{ pApplicationLayer },
		pWindow{ new Window() },
		pRenderer{ new Renderer() }
	{
		pInstance = this;
	}

	Engine::~Engine()
	{
		SAFE_RELEASE(pRenderer);
		SAFE_RELEASE(pWindow);
		SAFE_RELEASE(pApplicationLayer);
	}

	int32_t Engine::Start()
	{
		// Initialize GLFW Library
		if (!glfwInit())
		{
			std::cout << "Failed to initialize GLFW library!\n";
			return EXIT_FAILURE;
		}

		pWindow->Create();

		// Initialize GLAD
		if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
		{
			std::cout << "Failed to initialize GLAD!\n";
			return EXIT_FAILURE;
		}

		pRenderer->Setup();
		pApplicationLayer->Start();

		while (!pWindow->ShouldClose())
		{
			pRenderer->ClearScreen();
			pWindow->Update();
			pApplicationLayer->Update(0.f);
			pApplicationLayer->Render();
			pWindow->SwapBuffers();
		}

		pApplicationLayer->Release();
		pWindow->Destroy();

		return EXIT_SUCCESS;
	}
}