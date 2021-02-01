#include <gapspch.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/Application/ApplicationLayer.hpp>
#include <Core/Debugger/Debug.hpp>

MOD("Main");

class Game final : public gaps::ApplicationLayer
{
private:
	void OnStart() override
	{
		DEBUG_INFO("Game Starts");
	}
};

int32_t main()
{
	return gaps::Engine(new Game()).Start();
}