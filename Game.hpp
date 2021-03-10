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

class Game final : public gaps::ApplicationLayer, public gaps::EventHandler
{
public:
	Game();
	~Game() override;

private:
	void OnEnable() override;
	void OnDisable() override;
	void OnStart() override;
	void OnUpdate(float deltaTime) override;
	void OnRender() override;
	void OnRelease() override;

	bool Tick(gaps::TickEvent e);
	bool HandleKeyboard(gaps::KeyboardEvent e);
	bool HandleMouse(gaps::MouseEvent e);

	gaps::Texture* pBrickTexture = nullptr;
	gaps::Texture* pGapsTexture = nullptr;
	gaps::Shader* pShader = nullptr;
	gaps::VertexArray* pVertexArray = nullptr;
};