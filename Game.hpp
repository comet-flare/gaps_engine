#pragma once

#include <Core/Application/ApplicationLayer.hpp>

namespace gaps
{
	class Texture;
	class Shader;
	class VertexArray;
}

class Game final : public gaps::ApplicationLayer
{
public:
	Game();
	~Game();

private:
	void OnStart() override;
	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnRelease() override;

	gaps::Texture* pBrickTexture = nullptr;
	gaps::Texture* pGapsTexture = nullptr;
	gaps::Shader* pShader = nullptr;
	gaps::VertexArray* pVertexArray = nullptr;
};