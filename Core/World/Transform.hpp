#pragma once

namespace gaps
{
	struct TransformComponent final
	{
		glm::vec3 location{ 0.f };
		glm::vec3 rotation{ 0.f };
		glm::vec3 scale{ 1.f };
	};
}