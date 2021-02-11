#include <gapspch.hpp>
#include <Game.hpp>
#include <Core/Debugger/Debug.hpp>
#include <Core/Render/Shader/Shader.hpp>
#include <Core/Render/Pipeline/VertexArray.hpp>
#include <Core/Render/Texture/Texture.hpp>

MOD("Game");

Game::Game()
	:
	pBrickTexture{ new gaps::Texture() },
	pGapsTexture{ new gaps::Texture() },
	pShader{ new gaps::Shader() },
	pVertexArray{ new gaps::VertexArray() }
{
}

Game::~Game()
{
	SAFE_RELEASE(pVertexArray);
	SAFE_RELEASE(pShader);
	SAFE_RELEASE(pGapsTexture);
	SAFE_RELEASE(pBrickTexture);
}

void Game::OnStart()
{
	pShader->Load("BasicShader.vert", "BasicShader.frag");

	float vertices[] =
	{
		// position          // color              // tex coords
		 0.5f,  0.5f, 0.f,   1.f, 1.f, 1.f, 1.f,   1.f, 1.f, // top right
		 0.5f, -0.5f, 0.f,   1.f, 1.f, 1.f, 1.f,   1.f, 0.f, // bottom right
		-0.5f, -0.5f, 0.f,   1.f, 1.f, 1.f, 1.f,   0.f, 0.f, // bottom left
		-0.5f,  0.5f, 0.f,   1.f, 1.f, 1.f, 1.f,   0.f, 1.f  // top left
	};

	uint32_t indices[] =
	{
		0, 1, 3, // first triangle
		1, 2, 3  // second triangle
	};

	gaps::VertexLayoutMap vertexLayoutMap =
	{
		{ gaps::VertexAttributeId::Position, { 3, gaps::VertexAttributeType::Float } },
		{ gaps::VertexAttributeId::Color, { 4, gaps::VertexAttributeType::Float } },
		{ gaps::VertexAttributeId::TexCoord, { 2, gaps::VertexAttributeType::Float } }
	};

	pVertexArray->SetVertexBufferData(FROM_DATA(vertices), vertexLayoutMap);
	pVertexArray->SetIndexBufferData(FROM_DATA(indices));
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