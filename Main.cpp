#include <gapspch.hpp>
#include <Core/Engine/Engine.hpp>
#include <Game.hpp>

int32_t main()
{
	return gaps::Engine::Run([]() -> gaps::ApplicationLayer* { return new Game(); });
}