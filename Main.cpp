#include <gapspch.hpp>
#include <Core/Engine/Engine.hpp>
#include <Core/Application/ApplicationLayer.hpp>

class Game final : public gaps::ApplicationLayer
{
private:
	void OnStart() override
	{
		std::cout << "Game Starts\n";
	}

	void OnUpdate(float deltaTime) override
	{
		std::cout << "Updating..\n";
	}
};

int32_t main()
{
	std::cout << "GAPS Engine Entry Point reached!\n";

	return gaps::Engine(new Game()).Start();
}