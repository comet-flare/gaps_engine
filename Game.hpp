#pragma once

#include <Core/Application/ApplicationLayer.hpp>

namespace gaps
{
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

	gaps::Shader* pShader = nullptr;
	gaps::VertexArray* pVertexArray = nullptr;
};