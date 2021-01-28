#include <gapspch.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/System/Window.hpp>

namespace gaps
{
	Engine::Engine()
		:
		pWindow{ new Window() }
	{
		pInstance = this;
	}

	Engine::~Engine()
	{
		SAFE_RELEASE(pWindow);
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

		while (!pWindow->ShouldClose())
		{
			pWindow->Update();
			pWindow->SwapBuffers();
		}

		pWindow->Destroy();

		return EXIT_SUCCESS;
	}
}