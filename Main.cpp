#include <gapspch.hpp>
#include <Core/Engine/Engine.hpp>

int32_t main()
{
	std::cout << "GAPS Engine Entry Point reached!\n";

	return gaps::Engine().Start();
}