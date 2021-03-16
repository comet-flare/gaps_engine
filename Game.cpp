#include <gapspch.hpp>
#include <Game.hpp>
#include <Core/Debugger/Debug.hpp>
#include <Core/Render/Shader.hpp>
#include <Core/Render/Pipeline/VertexArray.hpp>
#include <Core/Render/Texture.hpp>
#include <Core/Input/Input.hpp>
#include <Core/Input/Keyboard/Keyboard.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/Render/Renderer.hpp>
#include <Core/World/Entity.hpp>
#include <Core/World/Transform.hpp>
#include <Core/Render/Camera.hpp>
#include <Core/Input/Mouse/Mouse.hpp>
#include <Core/Window/Window.hpp>

MOD("Game");

Game::Game()
	:
	pBrickTexture{ new Texture() },
	pShader{ new Shader() },
	pVertexArray{ new VertexArray() }
{
	TickHandler = [](const TickEvent& e) -> bool
	{
		// Update the cube's rotation
		{
			auto elapsedSeconds = Engine::GetElapsedSeconds();
			Entity cube = Engine::pScene->GetEntity("Cube1");
			auto& transform = cube.GetComponent<TransformComponent>();
			transform.rotation = { 0.f, elapsedSeconds, elapsedSeconds };
		}

		// Handle camera movement
		{
			auto camera = Engine::pScene->GetPrimaryCamera();

			if (Input::pKeyboard->IsKeyDown(KeyCode::W))
				Camera::MoveForward(camera, e.args.deltaTime);

			if (Input::pKeyboard->IsKeyDown(KeyCode::S))
				Camera::MoveBackward(camera, e.args.deltaTime);

			if (Input::pKeyboard->IsKeyDown(KeyCode::A))
				Camera::MoveLeft(camera, e.args.deltaTime);

			if (Input::pKeyboard->IsKeyDown(KeyCode::D))
				Camera::MoveRight(camera, e.args.deltaTime);

			if (Input::pKeyboard->IsKeyDown(KeyCode::Z))
				Camera::MoveUp(camera, e.args.deltaTime);

			if (Input::pKeyboard->IsKeyDown(KeyCode::X))
				Camera::MoveDown(camera, e.args.deltaTime);
		}

		return false;
	};

	MouseHandler = [](const MouseEvent& e) -> bool
	{
		static bool bFirstTime = true;

		switch (e.GetId())
		{
		case EventId::MouseScroll:
		{
			// Handle camera zoom in and zoom out
			auto camera = Engine::pScene->GetPrimaryCamera();
			Camera::Zoom(camera, e.args.yScroll);

			break;
		}
		case EventId::MouseMotion:
		{
			// Handle camera look around
			static float lastX = Engine::pWindow->GetDescriptor().width / 2.f;
			static float lastY = Engine::pWindow->GetDescriptor().height / 2.f;

			if (bFirstTime)
			{
				lastX = e.args.xPosition;
				lastY = e.args.yPosition;
			}

			float xOffset = e.args.xPosition - lastX;
			float yOffset = lastY - e.args.yPosition;

			lastX = e.args.xPosition;
			lastY = e.args.yPosition;

			auto camera = Engine::pScene->GetPrimaryCamera();
			Camera::LookAround(camera, xOffset, yOffset);

			bFirstTime = false;

			break;
		}
		case EventId::MouseButtonPress:
		{
			if (e.args.button == MouseButton::Left)
			{
				// Enable/Disable cursor on scene click
				static bool bToggle = false;
				bToggle = !bToggle;
				Input::pMouse->SetCursorEnabled(!bToggle);
				bFirstTime = !bFirstTime;
			}

			break;
		}
		default: break;
		}

		return false;
	};

	KeyboardHandler = [](const KeyboardEvent& e) -> bool
	{
		if (e.GetId() == EventId::KeyPress && e.args.key == KeyCode::Escape)
			Engine::ShutDown();

		return false;
	};
}

Game::~Game()
{
	SAFE_RELEASE(pVertexArray);
	SAFE_RELEASE(pShader);
	SAFE_RELEASE(pBrickTexture);
}

void Game::OnEnable()
{
	StartListening();
}

void Game::OnDisable()
{
	StopListening();
}

void Game::OnStart()
{
	Entity cube = Engine::pScene->CreateEntity("Cube1");
	auto& transform = cube.GetComponent<TransformComponent>();
	transform.location = { 0.5f, 0.5f, 0.0f };
	transform.scale = { 0.5f, 0.5f, 0.5f };

	pShader->Load("BasicShader.vert", "BasicShader.frag");
	Engine::pRenderer->shaders.push_back(pShader);

	float vertices[] =
	{
		// position             // color               // tex coords
		-0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,    1.f, 1.f, 1.f, 1.f,    0.0f, 1.0f
	};

	VertexLayoutMap vertexLayoutMap =
	{
		{ VertexAttributeId::Position, { 3, VertexAttributeType::Float } },
		{ VertexAttributeId::Color, { 4, VertexAttributeType::Float } },
		{ VertexAttributeId::TexCoord, { 2, VertexAttributeType::Float } }
	};

	pVertexArray->SetVertexBufferData(FROM_DATA(vertices), vertexLayoutMap);
	pVertexArray->Submit();

	pBrickTexture->Load("brick.png");

	pShader->Use();
	pShader->SetUniform("uColorTint", 1.f, 1.f, 1.f, 1.f);
	pShader->SetUniform("uTexture", 0);

	DEBUG_INFO("Demo Game Started Successfully!");
}

void Game::OnRender()
{
	pBrickTexture->Bind(0);

	pShader->Use();
	pVertexArray->Bind();
	pVertexArray->Draw();
}

void Game::OnRelease()
{
	pVertexArray->Release();
}