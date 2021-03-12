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

MOD("Game");

Game::Game()
	:
	pBrickTexture{ new gaps::Texture() },
	pGapsTexture{ new gaps::Texture() },
	pShader{ new gaps::Shader() },
	pVertexArray{ new gaps::VertexArray() }
{
	//TickHandler = BIND_EVENT(Game::Tick);
	//KeyboardHandler = BIND_EVENT(Game::HandleKeyboard);
	//MouseHandler = BIND_EVENT(Game::HandleMouse);
}

Game::~Game()
{
	SAFE_RELEASE(pVertexArray);
	SAFE_RELEASE(pShader);
	SAFE_RELEASE(pGapsTexture);
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
	gaps::Entity cube = gaps::Engine::pScene->CreateEntity("Cube1");
	auto& transform = cube.GetComponent<gaps::TransformComponent>();
	transform.location = { 0.5f, 0.5f, 0.0f };
	transform.scale = { 0.5f, 0.5f, 0.5f };

	pShader->Load("BasicShader.vert", "BasicShader.frag");
	gaps::Engine::pRenderer->shaders.push_back(pShader);

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

	gaps::VertexLayoutMap vertexLayoutMap =
	{
		{ gaps::VertexAttributeId::Position, { 3, gaps::VertexAttributeType::Float } },
		{ gaps::VertexAttributeId::Color, { 4, gaps::VertexAttributeType::Float } },
		{ gaps::VertexAttributeId::TexCoord, { 2, gaps::VertexAttributeType::Float } }
	};

	pVertexArray->SetVertexBufferData(FROM_DATA(vertices), vertexLayoutMap);
	pVertexArray->Submit();

	pBrickTexture->Load("brick.png");
	pGapsTexture->Load("gaps.png");

	pShader->Use();
	pShader->SetUniform("uTextureLerpRatio", 0.4f);
	pShader->SetUniform("uColorTint", 1.f, 1.f, 1.f, 1.f);
	pShader->SetUniform("uTexture0", 0);
	pShader->SetUniform("uTexture1", 1);

	DEBUG_INFO("Demo Game Started Successfully!");
}

void Game::OnUpdate(float deltaTime)
{
	auto elapsedSeconds = gaps::Engine::GetElapsedSeconds();
	gaps::Entity cube = gaps::Engine::pScene->GetEntity("Cube1");
	auto& transform = cube.GetComponent<gaps::TransformComponent>();
	transform.rotation = { 0.f, elapsedSeconds, elapsedSeconds };
}

void Game::OnRender()
{
	pBrickTexture->Bind(0);
	pGapsTexture->Bind(1);

	pShader->Use();
	pVertexArray->Bind();
	pVertexArray->Draw();
}

void Game::OnRelease()
{
	pVertexArray->Release();
}

bool Game::Tick(gaps::TickEvent e)
{
	std::cout << "DeltaTime: " << e.args.deltaTime
		<< "; ElapsedSeconds: " << gaps::Engine::GetElapsedSeconds() << "\n";

	return false;
}

bool Game::HandleKeyboard(gaps::KeyboardEvent e)
{
	std::cout << gaps::Input::pKeyboard->KeyToString(e.args.key);

	return false;
}

bool Game::HandleMouse(gaps::MouseEvent e)
{
	switch (e.GetId())
	{
	case gaps::EventId::MouseButtonPress:
	{
		std::cout << "Button DOWN: " << (int)e.args.button << "\n";
		break;
	}
	case gaps::EventId::MouseButtonRelease:
	{
		std::cout << "Button UP: " << (int)e.args.button << "\n";
		break;
	}
	case gaps::EventId::MouseMotion:
	{
		std::cout << "x_position: " << e.args.xPosition << "; y_position: " << e.args.yPosition << "\n";
		break;
	}
	case gaps::EventId::MouseScroll:
	{
		std::cout << "x_scroll: " << e.args.xScroll << "; y_scroll: " << e.args.yScroll << "\n";
		break;
	}
	default: break;
	}

	return false;
}