#include <gapspch.hpp>
#include <Game.hpp>
#include <Core/Debugger/Debug.hpp>
#include <Core/Render/Shader/Shader.hpp>
#include <Core/Render/Pipeline/VertexArray.hpp>

MOD("Game");

Game::Game()
	:
	pShader{ new gaps::Shader() },
	pVertexArray{ new gaps::VertexArray() }
{
}

Game::~Game()
{
	SAFE_RELEASE(pVertexArray);
	SAFE_RELEASE(pShader);
}

void Game::OnStart()
{
	pShader->Load("BasicShader.vert", "BasicShader.frag");

	float vertices[] =
	{
		// position          // color
		-0.5f, -0.5f, 0.0f,  1.f, 0.f, 0.f, 1.0f, // bottom left
		 0.5f, -0.5f, 0.0f,  0.f, 1.f, 0.f, 1.0f, // bottom right
		 0.0f,  0.5f, 0.0f,  0.f, 0.f, 1.f, 1.0f, // middle top
	};

	gaps::VertexLayoutMap vertexLayoutMap =
	{
		{ gaps::VertexAttributeId::Position, { 3, gaps::VertexAttributeType::Float } },
		{ gaps::VertexAttributeId::Color, { 4, gaps::VertexAttributeType::Float } }
	};

	pVertexArray->SetVertexBufferData(FROM_DATA(vertices), vertexLayoutMap);
	pVertexArray->Submit();

	DEBUG_INFO("Demo Game Started Successfully!");
}

void Game::OnUpdate(float deltaTime)
{
}

void Game::OnRender()
{
	pShader->Use();
	pVertexArray->Bind();
	pVertexArray->Draw();
}

void Game::OnRelease()
{
	pVertexArray->Release();
}