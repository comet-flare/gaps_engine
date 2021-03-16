#pragma once

#include <Core/Application/ApplicationLayer.hpp>
#include <Core/Event/EventHandler.hpp>
#include <Core/Input/Keyboard/KeyboardEvent.hpp>
#include <Core/Input/Mouse/MouseEvent.hpp>
#include <Core/Time/TickEvent.hpp>

namespace gaps
{
	class Texture;
	class Shader;
	class VertexArray;
}

using namespace gaps;

class Game final : public ApplicationLayer, public EventHandler
{
public:
	Game();
	~Game() override;

private:
	void OnEnable() override;
	void OnDisable() override;
	void OnStart() override;
	void OnRender() override;
	void OnRelease() override;

	Texture* pBrickTexture = nullptr;
	Shader* pShader = nullptr;
	VertexArray* pVertexArray = nullptr;
};