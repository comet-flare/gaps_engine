#include <gapspch.hpp>
#include <Core/Engine/Engine.hpp>
#include <Game.hpp>

int32_t main()
{
	return gaps::Engine([]() -> gaps::ApplicationLayer* { return new Game(); }).Start();
}